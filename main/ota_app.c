#include "ota_app.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "cJSON.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_ota_ops.h"
#include "esp_crt_bundle.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "app_config.h"
#include "tien_ich.h"
#include "node_comm.h"
#include "mqtt_app.h"

static const char *TAG = "OTA_APP";

#ifndef OTA_CHECK_URL
#define OTA_CHECK_URL "https://ota.thanhluan.io.vn/check_update.php"
#endif

static const char *OTA_STATE_NAMES[] = {"idle", "checking", "up_to_date", "available", "downloading",
                                        "rebooting", "failed", "busy", "sent"};
static const char *OTA_ERR_NAMES[]   = {"none", "no_wifi", "check_failed", "download_failed", "flash_failed",
                                        "node_unknown", "send_failed", "no_response"};
#define N_OTA_ST  ((int)(sizeof(OTA_STATE_NAMES) / sizeof(OTA_STATE_NAMES[0])))
#define N_OTA_ERR ((int)(sizeof(OTA_ERR_NAMES) / sizeof(OTA_ERR_NAMES[0])))

static volatile bool s_ota_busy = false;
static volatile bool s_ota_check_only = false;

static void publish_ota(const char *topic, const char *target, int state, int pct, int err,
                        uint32_t cur, uint32_t latest) {
    cJSON *o = cJSON_CreateObject();
    cJSON_AddStringToObject(o, "target",  target);
    cJSON_AddStringToObject(o, "state",   (state >= 0 && state < N_OTA_ST) ? OTA_STATE_NAMES[state] : "unknown");
    cJSON_AddNumberToObject(o, "pct",     pct);
    cJSON_AddNumberToObject(o, "current", cur);
    cJSON_AddNumberToObject(o, "latest",  latest);
    if (err) cJSON_AddStringToObject(o, "error", (err >= 0 && err < N_OTA_ERR) ? OTA_ERR_NAMES[err] : "unknown");
    char *str = cJSON_PrintUnformatted(o);
    if (str) {
        mqtt_pub(topic, str);
        ESP_LOGI(TAG, "[OTA %s] %s", target, str);
        cJSON_free(str);
    }
    cJSON_Delete(o);
}

static void ota_node_topic(const uint8_t *mac, char *id /*13*/, char *topic /*64*/) {
    mac_to_str(mac, id);
    snprintf(topic, 64, "home/node/%s/ota", id);
}

static void ota_send_node(const uint8_t *mac, bool check_only) {
    char id[13], topic[64];
    ota_node_topic(mac, id, topic);
    node_t *n = node_find(mac, false);
    if (!n) { publish_ota(topic, id, OTA_ST_FAILED, 0, OTA_ERR_NODE_UNKNOWN, 0, 0); return; }

    pkt_t p;
    init_cmd_hdr(&p, MSG_OTA_CMD, mac);
    if (check_only) p.flags |= FLAG_OTA_CHECK_ONLY;
    esp_err_t e = send_to_node(mac, &p);
    if (e != ESP_OK) { publish_ota(topic, id, OTA_ST_FAILED, 0, OTA_ERR_SEND, n->fw, 0); return; }

    n->ota_pending    = true;
    n->ota_check_only = check_only;
    n->ota_tries      = 1;
    n->ota_ms         = now_ms();
    publish_ota(topic, id, OTA_ST_SENT, 0, OTA_ERR_NONE, n->fw, 0);
}

void ota_retry(node_t *n, uint32_t now) {
    if (!n->ota_pending || now - n->ota_ms < 6000) return;
    char id[13], topic[64];
    ota_node_topic(n->mac, id, topic);
    if (n->ota_tries >= 3) {
        n->ota_pending = false;
        publish_ota(topic, id, OTA_ST_FAILED, 0, OTA_ERR_NO_RESPONSE, n->fw, 0);
        return;
    }
    n->ota_tries++;
    n->ota_ms = now;
    pkt_t p;
    init_cmd_hdr(&p, MSG_OTA_CMD, n->mac);
    if (n->ota_check_only) p.flags |= FLAG_OTA_CHECK_ONLY;
    send_to_node(n->mac, &p);
}

static int http_get_text(const char *url, char *buf, size_t cap) {
    esp_http_client_config_t cfg = {
        .url = url,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .timeout_ms = 10000,
    };
    esp_http_client_handle_t c = esp_http_client_init(&cfg);
    if (!c) return -1;
    int total = -1;
    if (esp_http_client_open(c, 0) == ESP_OK) {
        esp_http_client_fetch_headers(c);
        if (esp_http_client_get_status_code(c) == 200) {
            total = 0;
            while (total < (int)cap - 1) {
                int r = esp_http_client_read(c, buf + total, cap - 1 - total);
                if (r <= 0) break;
                total += r;
            }
            buf[total] = 0;
        }
        esp_http_client_close(c);
    }
    esp_http_client_cleanup(c);
    return total;
}

static void master_ota_status(int state, int pct, int err, uint32_t latest) {
    publish_ota("home/esp/ota/status", "master", state, pct, err, FW_VERSION, latest);
}

static void master_ota_run(bool check_only) {
    master_ota_status(OTA_ST_CHECKING, 0, OTA_ERR_NONE, 0);

    char url[200], body[512];
    snprintf(url, sizeof(url), "%s?type=master&v=%d", OTA_CHECK_URL, FW_VERSION);
    if (http_get_text(url, body, sizeof(body)) < 0) { master_ota_status(OTA_ST_FAILED, 0, OTA_ERR_CHECK, 0); return; }

    cJSON *j = cJSON_Parse(body);
    if (!j) { master_ota_status(OTA_ST_FAILED, 0, OTA_ERR_CHECK, 0); return; }
    bool has = cJSON_IsTrue(cJSON_GetObjectItem(j, "has_update"));
    const cJSON *lv = cJSON_GetObjectItem(j, "latest_version");
    const cJSON *bu = cJSON_GetObjectItem(j, "bin_url");
    uint32_t latest = cJSON_IsNumber(lv) ? (uint32_t)lv->valuedouble : 0;
    char bin[200] = {0};
    if (has && cJSON_IsString(bu) && bu->valuestring) strlcpy(bin, bu->valuestring, sizeof(bin));
    cJSON_Delete(j);

    if (!has)     { master_ota_status(OTA_ST_UP_TO_DATE, 0, OTA_ERR_NONE, FW_VERSION); return; }
    if (!bin[0])  { master_ota_status(OTA_ST_FAILED, 0, OTA_ERR_CHECK, latest); return; }
    if (check_only) { master_ota_status(OTA_ST_AVAILABLE, 0, OTA_ERR_NONE, latest); return; }

    ESP_LOGI(TAG, "OTA master: tai %s (v%d -> v%u)", bin, FW_VERSION, (unsigned)latest);
    master_ota_status(OTA_ST_DOWNLOADING, 0, OTA_ERR_NONE, latest);

    esp_http_client_config_t hc = {
        .url = bin,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .timeout_ms = 15000,
        .keep_alive_enable = true,
    };
    esp_https_ota_config_t oc = { .http_config = &hc };
    esp_https_ota_handle_t h = NULL;
    if (esp_https_ota_begin(&oc, &h) != ESP_OK) { master_ota_status(OTA_ST_FAILED, 0, OTA_ERR_DOWNLOAD, latest); return; }

    int total = esp_https_ota_get_image_size(h);
    int last = -10;
    esp_err_t e;
    while ((e = esp_https_ota_perform(h)) == ESP_ERR_HTTPS_OTA_IN_PROGRESS) {
        if (total > 0) {
            int pct = (int)((int64_t)esp_https_ota_get_image_len_read(h) * 100 / total);
            if (pct >= last + 10) {
                last = pct - pct % 10;
                master_ota_status(OTA_ST_DOWNLOADING, pct, OTA_ERR_NONE, latest);
            }
        }
    }

    if (e == ESP_OK && esp_https_ota_is_complete_data_received(h)) {
        if (esp_https_ota_finish(h) == ESP_OK) {
            master_ota_status(OTA_ST_REBOOTING, 100, OTA_ERR_NONE, latest);
            vTaskDelay(pdMS_TO_TICKS(2000));
            esp_restart();
        }
        master_ota_status(OTA_ST_FAILED, 0, OTA_ERR_FLASH, latest);
    } else {
        esp_https_ota_abort(h);
        ESP_LOGE(TAG, "OTA master loi: %s", esp_err_to_name(e));
        master_ota_status(OTA_ST_FAILED, 0, OTA_ERR_DOWNLOAD, latest);
    }
}

static void ota_task(void *arg) {
    master_ota_run(s_ota_check_only);
    s_ota_busy = false;
    vTaskDelete(NULL);
}

void handle_ota_cmd(const char *data, int dl) {
    cJSON *j = cJSON_ParseWithLength(data, dl);
    if (!j) { ESP_LOGW(TAG, "OTA cmd JSON loi"); return; }
    const cJSON *tg = cJSON_GetObjectItem(j, "target");
    const cJSON *mc = cJSON_GetObjectItem(j, "mac");
    bool check_only = cJSON_IsTrue(cJSON_GetObjectItem(j, "check_only"));

    if (cJSON_IsString(tg) && tg->valuestring && strcmp(tg->valuestring, "master") == 0) {
        if (s_ota_busy) {
            master_ota_status(OTA_ST_BUSY, 0, OTA_ERR_NONE, 0);
        } else {
            s_ota_busy = true;
            s_ota_check_only = check_only;
            if (xTaskCreate(ota_task, "ota", 10240, NULL, 3, NULL) != pdPASS) {
                s_ota_busy = false;
                master_ota_status(OTA_ST_FAILED, 0, OTA_ERR_DOWNLOAD, 0);
            }
        }
    } else if (cJSON_IsString(tg) && tg->valuestring && strcmp(tg->valuestring, "node") == 0
               && cJSON_IsString(mc) && mc->valuestring) {
        if (strcmp(mc->valuestring, "all") == 0) {
            for (int i = 0; i < MAX_NODES; i++) {
                node_t *n = get_node(i);
                if (n && n->used) ota_send_node(n->mac, check_only);
            }
        } else {
            uint8_t mac[6];
            if (strlen(mc->valuestring) == 12 && parse_mac_hex(mc->valuestring, mac)) ota_send_node(mac, check_only);
            else ESP_LOGW(TAG, "OTA: MAC khong hop le");
        }
    } else {
        ESP_LOGW(TAG, "OTA cmd khong hop le (target master|node)");
    }
    cJSON_Delete(j);
}

void handle_ota_status(const pkt_t *p) {
    node_t *n = node_find(p->h.src, false);
    if (n) { n->ota_pending = false; n->fw = p->fw_ver; }
    char id[13], topic[64];
    ota_node_topic(p->h.src, id, topic);
    publish_ota(topic, id, p->ota_state, p->ota_pct, p->ota_err, p->fw_ver, p->fw_new);
}
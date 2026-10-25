#include "node_comm.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "esp_log.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_mac.h"
#include "esp_netif.h"
#include "lwip/sockets.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "cJSON.h"

#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "host/util/util.h"

#include "app_config.h"
#include "tien_ich.h"
#include "mqtt_app.h"
#include "ota_app.h"

static const char *TAG = "NODE_COMM";

const char *AREAS[] = {"unassigned", "living_room", "bedroom", "kitchen", "bathroom", "other"};
const char *TYPES[] = {"unassigned", "light", "fan", "other"};
const int N_AREAS = sizeof(AREAS) / sizeof(AREAS[0]);
const int N_TYPES = sizeof(TYPES) / sizeof(TYPES[0]);

static node_t s_nodes[MAX_NODES];
static int s_sock = -1;
static uint8_t s_my_mac[6];
static const uint8_t BCAST[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static QueueHandle_t s_rx_q;

#define MAX_FOUND 8
static ble_addr_t s_found[MAX_FOUND];
static int s_found_n;
static uint8_t s_own_type;
static uint16_t s_conn = BLE_HS_CONN_HANDLE_NONE;
static uint16_t s_chr_handle;
static int s_result;
static prov_blob_t s_blob;
static volatile bool s_scanning = false;
static SemaphoreHandle_t s_sync_sem, s_scan_done_sem, s_step_sem, s_disc_sem;

static const ble_uuid128_t CHR_UUID = BLE_UUID128_INIT(
    0x01, 0xa0, 0x00, 0x1a, 0x5d, 0x7e, 0x53, 0x9a,
    0x6f, 0x4b, 0x0e, 0x4c, 0x02, 0x00, 0x1d, 0x5a);

const uint8_t *get_my_mac(void) {
    return s_my_mac;
}

node_t *get_node(int idx) {
    if (idx < 0 || idx >= MAX_NODES) return NULL;
    return &s_nodes[idx];
}

node_t *node_find(const uint8_t *mac, bool create) {
    node_t *free_slot = NULL;
    for (int i = 0; i < MAX_NODES; i++) {
        if (s_nodes[i].used) {
            if (memcmp(s_nodes[i].mac, mac, 6) == 0) return &s_nodes[i];
        } else if (!free_slot) {
            free_slot = &s_nodes[i];
        }
    }
    if (create && free_slot) {
        memset(free_slot, 0, sizeof(*free_slot));
        free_slot->used = true;
        memcpy(free_slot->mac, mac, 6);
        return free_slot;
    }
    return NULL;
}

static void ensure_peer(const uint8_t *mac) {
    if (esp_now_is_peer_exist(mac)) return;
    esp_now_peer_info_t p = {0};
    memcpy(p.peer_addr, mac, 6);
    p.channel = 0;
    p.ifidx   = WIFI_IF_STA;
    p.encrypt = false;
    esp_now_add_peer(&p);
}

void init_cmd_hdr(pkt_t *p, uint8_t type, const uint8_t *dst) {
    memset(p, 0, sizeof(*p));
    p->h.magic = PROTO_MAGIC;
    p->h.type  = type;
    p->h.ttl   = MAX_TTL;
    memcpy(p->h.src, s_my_mac, 6);
    memcpy(p->h.dst, dst, 6);
}

esp_err_t send_to_node(const uint8_t *mac, const pkt_t *p) {
    node_t *n = node_find(mac, false);
    if (!n) return ESP_ERR_NOT_FOUND;

    if (n->via_udp) {
        if (s_sock < 0) return ESP_FAIL;
        int r = sendto(s_sock, p, sizeof(*p), 0, (struct sockaddr *)&n->addr, sizeof(n->addr));
        return r == (int)sizeof(*p) ? ESP_OK : ESP_FAIL;
    }
    ensure_peer(n->next_mac);
    return esp_now_send(n->next_mac, (const uint8_t *)p, sizeof(*p));
}

esp_err_t send_relay_cmd(const uint8_t *mac, bool on) {
    pkt_t p;
    init_cmd_hdr(&p, MSG_CMD_RELAY, mac);
    p.relay = on ? 1 : 0;
    return send_to_node(mac, &p);
}

void handle_config(const uint8_t *mac, const char *data, int dl) {
    cJSON *j = cJSON_ParseWithLength(data, dl);
    if (!j) { ESP_LOGW(TAG, "Config JSON loi"); return; }

    const cJSON *name = cJSON_GetObjectItem(j, "name");
    int area  = lookup_idx(cJSON_GetObjectItem(j, "area"), AREAS, N_AREAS);
    int dtype = lookup_idx(cJSON_GetObjectItem(j, "type"), TYPES, N_TYPES);

    if (!cJSON_IsString(name) || !name->valuestring || !name->valuestring[0] || area < 0 || dtype < 0) {
        ESP_LOGW(TAG, "Config khong hop le (can name, area, type)");
    } else {
        pkt_t p;
        init_cmd_hdr(&p, MSG_CFG_SET, mac);
        p.area  = (uint8_t)area;
        p.dtype = (uint8_t)dtype;
        copy_name_utf8(p.name, NAME_LEN, name->valuestring);
        esp_err_t e = send_to_node(mac, &p);
        ESP_LOGI(TAG, "Config -> \"%s\" area=%s type=%s (%s)", p.name, AREAS[area], TYPES[dtype], esp_err_to_name(e));
    }
    cJSON_Delete(j);
}

static void publish_alert(const char *id, const char *name, const char *ev, const pkt_t *p) {
    char topic[64];
    snprintf(topic, sizeof(topic), "home/node/%s/alert", id);
    cJSON *o = cJSON_CreateObject();
    cJSON_AddStringToObject(o, "event",  ev);
    cJSON_AddStringToObject(o, "node",   id);
    cJSON_AddStringToObject(o, "name",   name);
    cJSON_AddNumberToObject(o, "temp",   round(p->temp * 10.0) / 10.0);
    cJSON_AddNumberToObject(o, "warn_c", p->warn_c);
    cJSON_AddNumberToObject(o, "cut_c",  p->cut_c);
    char *str = cJSON_PrintUnformatted(o);
    if (str) {
        mqtt_pub(topic, str);
        ESP_LOGW(TAG, "[ALERT %s] %s", id, str);
        cJSON_free(str);
    }
    cJSON_Delete(o);
}

static void handle_telemetry(const rx_item_t *it, const pkt_t *p) {
    node_t *n = node_find(p->h.src, true);
    if (!n) { ESP_LOGW(TAG, "Bang node day"); return; }

    n->via_udp = it->is_udp;
    n->hops    = p->h.hops;
    n->temp    = p->temp;
    n->lux     = p->lux;
    n->relay   = p->relay;
    n->warn_c  = p->warn_c;
    n->cut_c   = p->cut_c;
    n->last_ms = now_ms();
    n->fw      = p->fw_ver;
    if (it->is_udp) {
        n->addr = it->from;
        n->addr.sin_port = htons(UDP_PORT);
        pkt_t ack = {0};
        ack.h.magic = PROTO_MAGIC;
        ack.h.type  = MSG_ACK;
        memcpy(ack.h.src, s_my_mac, 6);
        memcpy(ack.h.dst, p->h.src, 6);
        sendto(s_sock, &ack, sizeof(ack), 0, (const struct sockaddr *)&it->from, sizeof(it->from));
    } else {
        memcpy(n->next_mac, it->from_mac, 6);
    }

    char id[13], topic[64];
    mac_to_str(p->h.src, id);
    snprintf(topic, sizeof(topic), "home/node/%s/telemetry", id);

    const char *via  = (p->h.hops > 0) ? "relay" : (it->is_udp ? "wifi" : "espnow");
    const char *link = p->link == LINK_WIFI ? "wifi" : (p->link == LINK_ESPNOW ? "espnow" : "none");

    char nm[NAME_LEN];
    memcpy(nm, p->name, NAME_LEN);
    nm[NAME_LEN - 1] = 0;

    cJSON *o = cJSON_CreateObject();
    cJSON_AddNumberToObject(o, "temp",   round(p->temp * 100.0) / 100.0);
    cJSON_AddNumberToObject(o, "light",  round(p->lux * 10.0) / 10.0);
    cJSON_AddNumberToObject(o, "relay",  p->relay);
    cJSON_AddNumberToObject(o, "hops",   p->h.hops);
    cJSON_AddStringToObject(o, "via",    via);
    cJSON_AddStringToObject(o, "link",   link);
    cJSON_AddNumberToObject(o, "rssi",   p->rssi);
    cJSON_AddBoolToObject  (o, "is_new", (p->flags & FLAG_NEW) != 0);
    cJSON_AddStringToObject(o, "name",   nm);
    cJSON_AddStringToObject(o, "area",   p->area  < N_AREAS ? AREAS[p->area]  : "unassigned");
    cJSON_AddStringToObject(o, "type",   p->dtype < N_TYPES ? TYPES[p->dtype] : "unassigned");
    cJSON_AddNumberToObject(o, "fw", p->fw_ver);
    cJSON *sf = cJSON_AddObjectToObject(o, "safety");
    cJSON_AddNumberToObject(sf, "warn_c",  p->warn_c);
    cJSON_AddNumberToObject(sf, "cut_c",   p->cut_c);
    cJSON_AddBoolToObject  (sf, "warn",    (p->flags & FLAG_OT_WARN) != 0);
    cJSON_AddBoolToObject  (sf, "tripped", (p->flags & FLAG_OT_TRIP) != 0);

    char *payload = cJSON_PrintUnformatted(o);
    if (payload) {
        mqtt_pub(topic, payload);
        ESP_LOGI(TAG, "[NODE %s] %s", id, payload);
        cJSON_free(payload);
    }
    cJSON_Delete(o);

    uint8_t prev = n->flags, cur = p->flags;
    n->flags = cur;
    const char *ev = NULL;
    if      ((cur & FLAG_OT_TRIP) && !(prev & FLAG_OT_TRIP)) ev = "overtemp_trip";
    else if (!(cur & FLAG_OT_TRIP) && (prev & FLAG_OT_TRIP)) ev = "trip_reset";
    else if ((cur & FLAG_OT_WARN) && !(prev & FLAG_OT_WARN)) ev = "overtemp_warn";
    else if (!(cur & FLAG_OT_WARN) && (prev & FLAG_OT_WARN)) ev = "overtemp_ok";
    if (ev) publish_alert(id, nm, ev, p);
}

static void master_rx_task(void *arg) {
    rx_item_t it;
    while (xQueueReceive(s_rx_q, &it, portMAX_DELAY)) {
        const pkt_t *p = (const pkt_t *)it.data;
        if (p->h.magic != PROTO_MAGIC) continue;
        if (p->h.type == MSG_TELEMETRY)       handle_telemetry(&it, p);
        else if (p->h.type == MSG_OTA_STATUS) handle_ota_status(p);
    }
}

static void udp_rx_task(void *arg) {
    s_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    struct sockaddr_in me = {0};
    me.sin_family      = AF_INET;
    me.sin_port        = htons(UDP_PORT);
    me.sin_addr.s_addr = htonl(INADDR_ANY);
    if (s_sock < 0 || bind(s_sock, (struct sockaddr *)&me, sizeof(me)) < 0) {
        ESP_LOGE(TAG, "UDP bind that bai");
        s_sock = -1;
        vTaskDelete(NULL);
        return;
    }
    ESP_LOGI(TAG, "UDP listen :%d", UDP_PORT);

    uint8_t buf[128];
    while (1) {
        rx_item_t it = {0};
        socklen_t sl = sizeof(it.from);
        int n = recvfrom(s_sock, buf, sizeof(buf), 0, (struct sockaddr *)&it.from, &sl);
        if (n != (int)sizeof(pkt_t)) continue;
        it.is_udp = true;
        memcpy(it.data, buf, n);
        xQueueSend(s_rx_q, &it, 0);
    }
}

static void espnow_recv_cb(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
    if (len != (int)sizeof(pkt_t)) return;
    rx_item_t it = {0};
    it.is_udp = false;
    memcpy(it.from_mac, info->src_addr, 6);
    memcpy(it.data, data, len);
    xQueueSend(s_rx_q, &it, 0);
}

static void beacon_task(void *arg) {
    uint16_t seq = 0;
    while (1) {
        pkt_t b = {0};
        b.h.magic = PROTO_MAGIC;
        b.h.type  = MSG_BEACON;
        b.h.ttl   = 1;
        b.h.hops  = 0;
        b.h.seq   = seq++;
        memcpy(b.h.src, s_my_mac, 6);
        esp_now_send(BCAST, (const uint8_t *)&b, sizeof(b));
        vTaskDelay(pdMS_TO_TICKS(BEACON_PERIOD_MS));
    }
}

static void ble_on_sync(void) {
    ble_hs_util_ensure_addr(0);
    ble_hs_id_infer_auto(0, &s_own_type);
    xSemaphoreGive(s_sync_sem);
}

static void ble_host_task(void *param) {
    nimble_port_run();
    nimble_port_freertos_deinit();
}

static int gap_scan_cb(struct ble_gap_event *ev, void *arg) {
    switch (ev->type) {
    case BLE_GAP_EVENT_DISC: {
        struct ble_hs_adv_fields f;
        if (ble_hs_adv_parse_fields(&f, ev->disc.data, ev->disc.length_data) != 0) break;
        size_t pl = strlen(BLE_NAME_PREFIX);
        if (f.name && f.name_len >= pl && memcmp(f.name, BLE_NAME_PREFIX, pl) == 0) {
            for (int i = 0; i < s_found_n; i++) {
                if (memcmp(s_found[i].val, ev->disc.addr.val, 6) == 0) return 0;
            }
            if (s_found_n < MAX_FOUND) {
                s_found[s_found_n++] = ev->disc.addr;
                ESP_LOGI(TAG, "BLE tim thay node %.*s", f.name_len, f.name);
            }
        }
        break;
    }
    case BLE_GAP_EVENT_DISC_COMPLETE:
        xSemaphoreGive(s_scan_done_sem);
        break;
    default: break;
    }
    return 0;
}

static int gap_conn_cb(struct ble_gap_event *ev, void *arg) {
    switch (ev->type) {
    case BLE_GAP_EVENT_CONNECT:
        if (ev->connect.status == 0) { s_conn = ev->connect.conn_handle; s_result = 0; }
        else                         { s_conn = BLE_HS_CONN_HANDLE_NONE;  s_result = -1; }
        xSemaphoreGive(s_step_sem);
        break;
    case BLE_GAP_EVENT_DISCONNECT:
        s_conn = BLE_HS_CONN_HANDLE_NONE;
        xSemaphoreGive(s_disc_sem);
        break;
    default: break;
    }
    return 0;
}

static int disc_chr_cb(uint16_t conn, const struct ble_gatt_error *err,
                       const struct ble_gatt_chr *chr, void *arg) {
    if (err->status == 0) { s_chr_handle = chr->val_handle; return 0; }
    xSemaphoreGive(s_step_sem);
    return 0;
}

static int write_cb(uint16_t conn, const struct ble_gatt_error *err,
                    struct ble_gatt_attr *attr, void *arg) {
    s_result = err->status;
    xSemaphoreGive(s_step_sem);
    return 0;
}

static bool wait_step(int ms) { 
    return xSemaphoreTake(s_step_sem, pdMS_TO_TICKS(ms)) == pdTRUE; 
}

static int provision_one(const ble_addr_t *addr) {
    int ret = -1;
    xSemaphoreTake(s_step_sem, 0);
    xSemaphoreTake(s_disc_sem, 0);

    s_result = -1;
    if (ble_gap_connect(s_own_type, addr, 5000, NULL, gap_conn_cb, NULL) != 0) return -1;
    if (!wait_step(6000) || s_result != 0) { ble_gap_conn_cancel(); return -1; }

    s_chr_handle = 0;
    if (ble_gattc_disc_chrs_by_uuid(s_conn, 1, 0xFFFF, &CHR_UUID.u, disc_chr_cb, NULL) == 0) {
        wait_step(5000);
    }

    if (s_chr_handle) {
        struct os_mbuf *om = ble_hs_mbuf_from_flat(&s_blob, sizeof(s_blob));
        s_result = -1;
        if (om && ble_gattc_write_long(s_conn, s_chr_handle, 0, om, write_cb, NULL) == 0) {
            if (wait_step(8000) && s_result == 0) ret = 0;
        }
    }

    if (s_conn != BLE_HS_CONN_HANDLE_NONE) {
        ble_gap_terminate(s_conn, BLE_ERR_REM_USER_CONN_TERM);
        xSemaphoreTake(s_disc_sem, pdMS_TO_TICKS(3000));
    }
    ESP_LOGI(TAG, "Provision node: %s", ret == 0 ? "OK" : "FAIL");
    return ret;
}

static void build_blob(prov_blob_t *b) {
    memset(b, 0, sizeof(*b));
    b->magic = PROV_MAGIC;
    strlcpy(b->ssid, WIFI_SSID, sizeof(b->ssid));
    strlcpy(b->pass, WIFI_PASS, sizeof(b->pass));
    wifi_ap_record_t ap;
    if (esp_wifi_sta_get_ap_info(&ap) == ESP_OK) b->channel = ap.primary;
    esp_read_mac(b->master_mac, ESP_MAC_WIFI_STA);
    esp_netif_t *netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    esp_netif_ip_info_t ip;
    if (netif && esp_netif_get_ip_info(netif, &ip) == ESP_OK) b->master_ip = ip.ip.addr;
}

static void publish_scan_status(const char *status, int found, int ok) {
    char payload[96];
    snprintf(payload, sizeof(payload),
             "{\"status\": \"%s\", \"found\": %d, \"provisioned\": %d}", status, found, ok);
    mqtt_pub(TOPIC_SCAN_RESULT, payload);
}

static void scan_task(void *arg) {
    int ok = 0;
    s_found_n = 0;
    build_blob(&s_blob);
    publish_scan_status("scanning", 0, 0);
    xSemaphoreTake(s_sync_sem, 0);
    xSemaphoreTake(s_scan_done_sem, 0);

    if (nimble_port_init() == ESP_OK) {
        ble_hs_cfg.sync_cb = ble_on_sync;
        nimble_port_freertos_init(ble_host_task);

        if (xSemaphoreTake(s_sync_sem, pdMS_TO_TICKS(5000)) == pdTRUE) {
            struct ble_gap_disc_params dp = {0};
            dp.passive = 1;
            dp.filter_duplicates = 1;
            if (ble_gap_disc(s_own_type, BLE_SCAN_MS, &dp, gap_scan_cb, NULL) == 0) {
                xSemaphoreTake(s_scan_done_sem, pdMS_TO_TICKS(BLE_SCAN_MS + 2000));
                ESP_LOGI(TAG, "BLE quet xong: %d node", s_found_n);
                for (int i = 0; i < s_found_n; i++) {
                    if (provision_one(&s_found[i]) == 0) ok++;
                }
            }
        }
        nimble_port_stop();
        nimble_port_deinit();
    } else {
        ESP_LOGE(TAG, "Khong bat duoc BLE");
    }

    publish_scan_status("done", s_found_n, ok);
    s_scanning = false;
    vTaskDelete(NULL);
}

void start_scan(void) {
    if (s_scanning) { ESP_LOGW(TAG, "Dang quet roi"); return; }
    s_scanning = true;
    if (xTaskCreate(scan_task, "ble_scan", 8192, NULL, 5, NULL) != pdPASS) s_scanning = false;
}

void espnow_start(void) {
    esp_read_mac(s_my_mac, ESP_MAC_WIFI_STA);
    esp_wifi_set_ps(WIFI_PS_NONE);

    s_rx_q = xQueueCreate(16, sizeof(rx_item_t));
    s_sync_sem      = xSemaphoreCreateBinary();
    s_scan_done_sem = xSemaphoreCreateBinary();
    s_step_sem      = xSemaphoreCreateBinary();
    s_disc_sem      = xSemaphoreCreateBinary();

    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(espnow_recv_cb));
    ensure_peer(BCAST);

    xTaskCreate(master_rx_task, "master_rx", 4096, NULL, 5, NULL);
    xTaskCreate(udp_rx_task,    "udp_rx",    4096, NULL, 5, NULL);
    xTaskCreate(beacon_task,    "beacon",    2048, NULL, 4, NULL);
}
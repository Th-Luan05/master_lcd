#include "automation.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "esp_log.h"
#include "nvs_flash.h"
#include "cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "app_config.h"
#include "app_types.h"
#include "tien_ich.h"
#include "node_comm.h"
#include "mqtt_app.h"
#include "ota_app.h"

static const char *TAG = "AUTOMATION";
static rule_t s_rules[MAX_RULES];
static rule_rt_t s_rt[MAX_RULES];
static SemaphoreHandle_t s_rules_mux;

enum { RULE_TIME = 1, RULE_SENSOR = 2 };
enum { METRIC_TEMP = 0, METRIC_LIGHT = 1 };
enum { OP_GT = 0, OP_LT = 1 };

esp_err_t request_relay(const uint8_t *mac, bool on) {
    node_t *n = node_find(mac, false);
    if (!n) return ESP_ERR_NOT_FOUND;
    n->want_valid = true;
    n->want_on    = on;
    n->want_tries = 1;
    n->want_ms    = now_ms();
    return send_relay_cmd(mac, on);
}

static void reconcile_nodes(void) {
    uint32_t now = now_ms();
    for (int i = 0; i < MAX_NODES; i++) {
        node_t *n = get_node(i);
        if (!n || !n->used) continue;
        ota_retry(n, now);
        if (!n->want_valid) continue;
        if (n->relay == (n->want_on ? 1 : 0)) { n->want_valid = false; continue; }
        if (n->want_on && (n->flags & FLAG_OT_TRIP)) { n->want_valid = false; continue; }
        if (now - n->want_ms < 4000) continue;
        if (n->want_tries >= 3) {
            ESP_LOGW(TAG, "Relay khong dat trang thai mong muon sau 3 lan, bo qua");
            n->want_valid = false;
            continue;
        }
        n->want_tries++;
        n->want_ms = now;
        send_relay_cmd(n->mac, n->want_on);
    }
}

static void rule_fire(int id, const uint8_t *target, bool on) {
    char mac[13], payload[96];
    mac_to_str(target, mac);
    esp_err_t e = request_relay(target, on);
    ESP_LOGI(TAG, "Rule %d -> %s %s (%s)", id, mac, on ? "ON" : "OFF", esp_err_to_name(e));
    snprintf(payload, sizeof(payload), "{\"rule\": %d, \"target\": \"%s\", \"action\": \"%s\", \"ok\": %s}",
             id, mac, on ? "on" : "off", e == ESP_OK ? "true" : "false");
    mqtt_pub("home/esp/automation/event", payload);
}

static bool in_window(const rule_t *r, int m) {
    if (r->win_from < 0) return true;
    if (r->win_from <= r->win_to) return m >= r->win_from && m < r->win_to;
    return m >= r->win_from || m < r->win_to;
}

static void rules_save(void) {
    nvs_handle_t h;
    if (nvs_open("auto", NVS_READWRITE, &h) != ESP_OK) return;
    nvs_set_blob(h, "rules", s_rules, sizeof(s_rules));
    nvs_commit(h);
    nvs_close(h);
}

static void rules_load(void) {
    memset(s_rules, 0, sizeof(s_rules));
    nvs_handle_t h;
    if (nvs_open("auto", NVS_READONLY, &h) == ESP_OK) {
        static rule_t tmp[MAX_RULES];
        size_t n = sizeof(tmp);
        if (nvs_get_blob(h, "rules", tmp, &n) == ESP_OK && n == sizeof(tmp)) memcpy(s_rules, tmp, sizeof(tmp));
        nvs_close(h);
    }
    for (int i = 0; i < MAX_RULES; i++) { s_rt[i].active = false; s_rt[i].last_key = -1; }
}

static int parse_hm(const cJSON *it) {
    if (!cJSON_IsString(it) || !it->valuestring) return -1;
    int h, m;
    if (sscanf(it->valuestring, "%d:%d", &h, &m) != 2) return -1;
    if (h < 0 || h > 23 || m < 0 || m > 59) return -1;
    return h * 60 + m;
}

static bool parse_mac_item(const cJSON *it, uint8_t *out) {
    return cJSON_IsString(it) && it->valuestring && strlen(it->valuestring) == 12 && parse_mac_hex(it->valuestring, out);
}

static bool parse_rule(const cJSON *j, rule_t *r) {
    memset(r, 0, sizeof(*r));
    r->used    = 1;
    r->enabled = cJSON_IsFalse(cJSON_GetObjectItem(j, "en")) ? 0 : 1;

    const cJSON *act = cJSON_GetObjectItem(j, "action");
    if (!cJSON_IsString(act) || !act->valuestring) return false;
    if (strcmp(act->valuestring, "on") == 0)       r->action = 1;
    else if (strcmp(act->valuestring, "off") == 0) r->action = 0;
    else return false;

    if (!parse_mac_item(cJSON_GetObjectItem(j, "target"), r->target)) return false;

    const cJSON *ty = cJSON_GetObjectItem(j, "type");
    if (!cJSON_IsString(ty) || !ty->valuestring) return false;

    if (strcmp(ty->valuestring, "time") == 0) {
        r->type   = RULE_TIME;
        r->at_min = (int16_t)parse_hm(cJSON_GetObjectItem(j, "time"));
        if (r->at_min < 0) return false;
        const cJSON *days = cJSON_GetObjectItem(j, "days");
        if (cJSON_IsArray(days)) {
            const cJSON *d;
            cJSON_ArrayForEach(d, days) {
                if (!cJSON_IsNumber(d) || d->valueint < 0 || d->valueint > 6) return false;
                r->days |= (uint8_t)(1u << d->valueint);
            }
        }
        if (!r->days) r->days = 0x7F;
    } else if (strcmp(ty->valuestring, "sensor") == 0) {
        r->type = RULE_SENSOR;
        if (!parse_mac_item(cJSON_GetObjectItem(j, "src"), r->src)) return false;

        const cJSON *m = cJSON_GetObjectItem(j, "metric");
        if (!cJSON_IsString(m) || !m->valuestring) return false;
        if (strcmp(m->valuestring, "temp") == 0)       r->metric = METRIC_TEMP;
        else if (strcmp(m->valuestring, "light") == 0) r->metric = METRIC_LIGHT;
        else return false;

        const cJSON *op = cJSON_GetObjectItem(j, "op");
        if (!cJSON_IsString(op) || !op->valuestring) return false;
        if (strcmp(op->valuestring, ">") == 0)      r->op = OP_GT;
        else if (strcmp(op->valuestring, "<") == 0) r->op = OP_LT;
        else return false;

        const cJSON *v = cJSON_GetObjectItem(j, "value");
        if (!cJSON_IsNumber(v)) return false;
        r->value = (float)v->valuedouble;

        const cJSON *hy = cJSON_GetObjectItem(j, "hyst");
        if (hy) {
            if (!cJSON_IsNumber(hy) || hy->valuedouble < 0) return false;
            r->hyst = (float)hy->valuedouble;
        }
        r->revert = cJSON_IsTrue(cJSON_GetObjectItem(j, "revert")) ? 1 : 0;

        const cJSON *from = cJSON_GetObjectItem(j, "from");
        const cJSON *to   = cJSON_GetObjectItem(j, "to");
        if (from || to) {
            r->win_from = (int16_t)parse_hm(from);
            r->win_to   = (int16_t)parse_hm(to);
            if (r->win_from < 0 || r->win_to < 0 || r->win_from == r->win_to) return false;
        } else {
            r->win_from = -1;
            r->win_to   = -1;
        }
    } else {
        return false;
    }
    return true;
}

static cJSON *rule_to_json(int id) {
    const rule_t *r = &s_rules[id];
    char mac[13], hm[16];
    cJSON *o = cJSON_CreateObject();
    cJSON_AddNumberToObject(o, "id", id);
    cJSON_AddBoolToObject(o, "en", r->enabled);
    mac_to_str(r->target, mac);
    cJSON_AddStringToObject(o, "target", mac);
    cJSON_AddStringToObject(o, "action", r->action ? "on" : "off");

    if (r->type == RULE_TIME) {
        cJSON_AddStringToObject(o, "type", "time");
        snprintf(hm, sizeof(hm), "%02d:%02d", r->at_min / 60, r->at_min % 60);
        cJSON_AddStringToObject(o, "time", hm);
        cJSON *d = cJSON_AddArrayToObject(o, "days");
        for (int k = 0; k < 7; k++) {
            if (r->days & (1 << k)) cJSON_AddItemToArray(d, cJSON_CreateNumber(k));
        }
    } else {
        cJSON_AddStringToObject(o, "type", "sensor");
        mac_to_str(r->src, mac);
        cJSON_AddStringToObject(o, "src", mac);
        cJSON_AddStringToObject(o, "metric", r->metric == METRIC_TEMP ? "temp" : "light");
        cJSON_AddStringToObject(o, "op", r->op == OP_GT ? ">" : "<");
        cJSON_AddNumberToObject(o, "value", round(r->value * 100.0) / 100.0);
        cJSON_AddNumberToObject(o, "hyst",  round(r->hyst * 100.0) / 100.0);
        cJSON_AddBoolToObject(o, "revert", r->revert);
        if (r->win_from >= 0) {
            snprintf(hm, sizeof(hm), "%02d:%02d", r->win_from / 60, r->win_from % 60);
            cJSON_AddStringToObject(o, "from", hm);
            snprintf(hm, sizeof(hm), "%02d:%02d", r->win_to / 60, r->win_to % 60);
            cJSON_AddStringToObject(o, "to", hm);
        }
    }
    return o;
}

static void publish_rule(int id) {
    char topic[40];
    snprintf(topic, sizeof(topic), "home/esp/rule/%d", id);
    if (!s_rules[id].used) { mqtt_pub_r(topic, "", 1); return; }
    cJSON *o = rule_to_json(id);
    char *str = cJSON_PrintUnformatted(o);
    if (str) { mqtt_pub_r(topic, str, 1); cJSON_free(str); }
    cJSON_Delete(o);
}

void publish_all_rules(void) {
    xSemaphoreTake(s_rules_mux, portMAX_DELAY);
    for (int i = 0; i < MAX_RULES; i++) publish_rule(i);
    xSemaphoreGive(s_rules_mux);
}

void handle_rule_set(int id, const char *data, int dl) {
    if (id < 0 || id >= MAX_RULES) { ESP_LOGW(TAG, "Rule id ngoai 0..%d", MAX_RULES - 1); return; }

    rule_t r;
    bool del = (dl == 0);
    if (!del) {
        cJSON *j = cJSON_ParseWithLength(data, dl);
        bool ok = j && parse_rule(j, &r);
        cJSON_Delete(j);
        if (!ok) { ESP_LOGW(TAG, "Rule %d khong hop le", id); return; }
    }

    xSemaphoreTake(s_rules_mux, portMAX_DELAY);
    if (del) memset(&s_rules[id], 0, sizeof(s_rules[id]));
    else     s_rules[id] = r;
    s_rt[id].active   = false;
    s_rt[id].last_key = -1;
    rules_save();
    publish_rule(id);
    xSemaphoreGive(s_rules_mux);
    ESP_LOGI(TAG, "Rule %d %s", id, del ? "da xoa" : "da luu");
}

void handle_safety(const uint8_t *mac, const char *data, int dl) {
    node_t *n = node_find(mac, false);
    if (!n) { ESP_LOGW(TAG, "Safety: chua biet node nay (cho node gui telemetry)"); return; }
    cJSON *j = cJSON_ParseWithLength(data, dl);
    if (!j) { ESP_LOGW(TAG, "Safety JSON loi"); return; }

    int warn = n->warn_c, cut = n->cut_c;
    bool ok = true;
    const cJSON *w = cJSON_GetObjectItem(j, "warn_c");
    const cJSON *c = cJSON_GetObjectItem(j, "cut_c");
    if (w) { if (cJSON_IsNumber(w)) warn = (int)w->valuedouble; else ok = false; }
    if (c) { if (cJSON_IsNumber(c)) cut  = (int)c->valuedouble;  else ok = false; }
    if (warn < 0 || warn > 150 || cut < 0 || cut > 150) ok = false;
    if (warn > 0 && cut > 0 && warn >= cut) ok = false;

    if (!ok) {
        ESP_LOGW(TAG, "Safety khong hop le (0..150, warn < cut, 0 = tat)");
    } else {
        pkt_t p;
        init_cmd_hdr(&p, MSG_SAFETY_SET, mac);
        p.warn_c = (int16_t)warn;
        p.cut_c  = (int16_t)cut;
        if (cJSON_IsTrue(cJSON_GetObjectItem(j, "clear"))) p.flags |= FLAG_CLEAR_TRIP;
        esp_err_t e = send_to_node(mac, &p);
        ESP_LOGI(TAG, "Safety warn=%d cut=%d clear=%d (%s)", warn, cut, (p.flags & FLAG_CLEAR_TRIP) ? 1 : 0, esp_err_to_name(e));
    }
    cJSON_Delete(j);
}

static void automation_task(void *arg) {
    int memory_log_counter = 0;
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));

        if (++memory_log_counter >= 60) {
            memory_log_counter = 0;
            log_memory_usage();
        }

        bool tv = time_valid();
        struct tm tm = {0};
        int now_min = 0, key = -1;
        if (tv) {
            time_t t;
            time(&t);
            localtime_r(&t, &tm);
            now_min = tm.tm_hour * 60 + tm.tm_min;
            key     = tm.tm_yday * 1440 + now_min;
        }
        uint32_t now = now_ms();

        xSemaphoreTake(s_rules_mux, portMAX_DELAY);
        for (int i = 0; i < MAX_RULES; i++) {
            rule_t *r = &s_rules[i];
            rule_rt_t *rt = &s_rt[i];
            if (!r->used || !r->enabled) continue;

            if (r->type == RULE_TIME) {
                if (!tv || key == rt->last_key) continue;
                if (now_min == r->at_min && (r->days & (1 << tm.tm_wday))) {
                    rt->last_key = key;
                    rule_fire(i, r->target, r->action);
                }
            } else {
                node_t *s = node_find(r->src, false);
                if (!s || (now - s->last_ms) > SENSOR_STALE_MS) continue;
                if (r->win_from >= 0 && !tv) continue;

                float v    = (r->metric == METRIC_TEMP) ? s->temp : s->lux;
                bool  trig = (r->op == OP_GT) ? (v > r->value) : (v < r->value);
                bool  rel  = (r->op == OP_GT) ? (v < r->value - r->hyst) : (v > r->value + r->hyst);
                bool  win  = in_window(r, now_min);
                bool  next = rt->active ? !(rel || !win) : (trig && win);

                if (next != rt->active) {
                    rt->active = next;
                    if (next)              rule_fire(i, r->target, r->action);
                    else if (r->revert)    rule_fire(i, r->target, !r->action);
                }
            }
        }
        xSemaphoreGive(s_rules_mux);

        reconcile_nodes();
    }
}

void automation_init(void) {
    s_rules_mux = xSemaphoreCreateMutex();
    rules_load();
    xTaskCreate(automation_task, "automation", 4096, NULL, 4, NULL);
}
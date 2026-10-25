#include "mqtt_app.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "mqtt_client.h"
#include "esp_crt_bundle.h"
#include "esp_ota_ops.h"

#include "app_config.h"
#include "tien_ich.h"
#include "node_comm.h"
#include "automation.h"
#include "ota_app.h"

static const char *TAG = "MQTT_APP";
static esp_mqtt_client_handle_t s_mqtt_client = NULL;
static bool s_mqtt_connected = false;

void mqtt_pub_r(const char *topic, const char *payload, int retain) {
    if (!s_mqtt_connected || !s_mqtt_client) return;
    esp_mqtt_client_publish(s_mqtt_client, topic, payload, 0, 1, retain);
}

void mqtt_pub(const char *topic, const char *payload) {
    mqtt_pub_r(topic, payload, 0);
}

static void handle_mqtt_message(const char *topic, int tl, const char *data, int dl) {
    if (bytes_is(topic, tl, TOPIC_COMMAND)) {
        if (bytes_is(data, dl, "scan") || bytes_is(data, dl, "SCAN")) {
            ESP_LOGI(TAG, "Lenh SCAN -> bat BLE");
            start_scan();
        }
        return;
    }
    if (bytes_is(topic, tl, TOPIC_OTA_CMD)) {
        handle_ota_cmd(data, dl);
        return;
    }
    if (tl > 14 + 4 && memcmp(topic, "home/esp/rule/", 14) == 0 && memcmp(topic + tl - 4, "/set", 4) == 0) {
        int idl = tl - 14 - 4;
        if (idl >= 1 && idl <= 2) {
            char num[3] = {0};
            memcpy(num, topic + 14, idl);
            char *end;
            long id = strtol(num, &end, 10);
            if (*end == 0) handle_rule_set((int)id, data, dl);
        }
        return;
    }
    if (tl > 23 && memcmp(topic, "home/node/", 10) == 0 && topic[22] == '/') {
        char hex[13];
        memcpy(hex, topic + 10, 12);
        hex[12] = 0;
        uint8_t mac[6];
        if (!parse_mac_hex(hex, mac)) return;
        const char *verb = topic + 23;
        int vl = tl - 23;

        if (bytes_is(verb, vl, "set")) {
            bool on;
            if (bytes_is(data, dl, "ON"))       on = true;
            else if (bytes_is(data, dl, "OFF")) on = false;
            else return;
            esp_err_t e = send_relay_cmd(mac, on);
            ESP_LOGI(TAG, "Relay %s -> %s (%s)", hex, on ? "ON" : "OFF", esp_err_to_name(e));
        } else if (bytes_is(verb, vl, "config")) {
            handle_config(mac, data, dl);
        } else if (bytes_is(verb, vl, "safety")) {
            handle_safety(mac, data, dl);
        }
    }
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT Connected to Broker via WSS!");
        s_mqtt_connected = true;
        esp_mqtt_client_subscribe(s_mqtt_client, TOPIC_COMMAND, 0);
        esp_mqtt_client_subscribe(s_mqtt_client, TOPIC_NODE_SET, 0);
        esp_mqtt_client_subscribe(s_mqtt_client, TOPIC_NODE_CFG, 0);
        esp_mqtt_client_subscribe(s_mqtt_client, TOPIC_NODE_SAFETY, 0);
        esp_mqtt_client_subscribe(s_mqtt_client, TOPIC_RULE_SET, 0);
        publish_all_rules();
        esp_mqtt_client_subscribe(s_mqtt_client, TOPIC_OTA_CMD, 0);
        {
            char info[32];
            snprintf(info, sizeof(info), "{\"fw\": %d}", FW_VERSION);
            mqtt_pub_r("home/esp/info", info, 1);
        }
#ifdef CONFIG_BOOTLOADER_APP_ROLLBACK_ENABLE
        esp_ota_mark_app_valid_cancel_rollback();
#endif
        break;

    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGW(TAG, "MQTT Disconnected!");
        s_mqtt_connected = false;
        break;

    case MQTT_EVENT_DATA:
        if (event->current_data_offset != 0 || event->data_len != event->total_data_len) {
            ESP_LOGW(TAG, "MQTT payload bi chia manh (>buffer), bo qua");
            break;
        }
        ESP_LOGI(TAG, "[MQTT RX] %.*s = %.*s", event->topic_len, event->topic, event->data_len, event->data);
        handle_mqtt_message(event->topic, event->topic_len, event->data, event->data_len);
        break;

    case MQTT_EVENT_ERROR:
        ESP_LOGE(TAG, "MQTT_EVENT_ERROR, error_type=%d", event->error_handle->error_type);
        break;

    default:
        break;
    }
}

void mqtt_app_start(void) {
    const esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {
            .address = { .uri = MQTT_BROKER_URI },
            .verification = { .crt_bundle_attach = esp_crt_bundle_attach },
        },
        .credentials = {
            .username = MQTT_USERNAME,
            .authentication = { .password = MQTT_PASSWORD },
        },
    };

    s_mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(s_mqtt_client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(s_mqtt_client);
}
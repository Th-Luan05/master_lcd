#ifndef APP_CONFIG_H
#define APP_CONFIG_H


#include <stdint.h>
#include "esp_err.h"

#define WIFI_SSID           "Hoi Chu Tro"
#define WIFI_PASS           "bodeocho"
#define WIFI_CONNECTED_BIT  BIT0

#define MQTT_BROKER_URI     "wss://mqtt.thanhluan.io.vn/mqtt"
#define MQTT_USERNAME       "esp32_node1"
#define MQTT_PASSWORD       "080305"

#define TOPIC_COMMAND       "home/esp/command"
#define TOPIC_SCAN_RESULT   "home/esp/scan/result"
#define TOPIC_NODE_SET      "home/node/+/set"
#define TOPIC_NODE_CFG      "home/node/+/config"
#define TOPIC_NODE_SAFETY   "home/node/+/safety"
#define TOPIC_RULE_SET      "home/esp/rule/+/set"
#define TOPIC_OTA_CMD       "home/esp/ota/cmd"

#define TZ_POSIX            "ICT-7"
#define MAX_RULES           16
#define SENSOR_STALE_MS     30000
#define FW_VERSION          1

#define BLE_SCAN_MS         8000
#define MAX_NODES           16
#define BEACON_PERIOD_MS    3000


// Khoi tao PWM den nen
esp_err_t lcd_backlight_init(void);

// Dieu chinh do sang: 0-100%
esp_err_t lcd_set_brightness(uint8_t brightness);

#endif
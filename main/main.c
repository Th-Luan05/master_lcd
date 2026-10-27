/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"
#include "ui/ui.h"
#include "giaodien.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_wifi.h"

#include "app_config.h"
#include "app_types.h"
#include "tien_ich.h"
#include "node_comm.h"
#include "automation.h"
#include "ota_app.h"
#include "mqtt_app.h"
#include "giaodien.h"
#include "LCD.h"
#include "wifi_mgr.h"

#define TAG "ESP-MAIN"



void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(lcd_init());
    ESP_ERROR_CHECK(lcd_touch_calibrate());

    ESP_LOGI(TAG, "Khoi dong WiFi...");
    wifi_mgr_init();          // khong block, tu ket noi WiFi da luu
    init_display();           // UI + gan event WiFi

    espnow_start();
    time_start();
    automation_init();
    mqtt_app_start();         // client tu reconnect khi co mang
}
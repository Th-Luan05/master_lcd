/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "LCD.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"
#include "ui/ui.h"


#define TAG "ESP-EXAMPLE"

void app_main(void)
{
    ESP_ERROR_CHECK(lcd_init());

    /* Add and show objects on display */
    if (lvgl_port_lock(0)) {
        ui_init();
        lvgl_port_unlock();
    }

    ESP_LOGI(TAG, "Example initialization done.");
}

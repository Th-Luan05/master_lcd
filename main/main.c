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
#include "giaodien.h"


#define TAG "ESP-EXAMPLE"

void app_main(void)
{
    ESP_ERROR_CHECK(lcd_init());

    /* Hieu chinh cam ung: cham lan luot 4 cham tron o 4 goc */
    ESP_ERROR_CHECK(lcd_touch_calibrate());
    init_display();

    /* Add and show objects on display */
    

    ESP_LOGI(TAG, "Example initialization done.");
}
#ifndef WIFI_MGR_H
#define WIFI_MGR_H

#include <stdbool.h>
#include "esp_err.h"
#include "esp_wifi_types.h"

/* Khoi dong WiFi STA (KHONG block). Neu NVS co WiFi da luu thi tu ket noi. */
void wifi_mgr_init(void);

/* Quet WiFi (block ~2-4s) - goi tu task rieng, KHONG goi tu task LVGL.
 * Tra ve so AP, da bo SSID rong/trung. */
int wifi_mgr_scan(wifi_ap_record_t *out, int max);

/* Ket noi WiFi moi. Chi luu NVS khi ket noi thanh cong. */
esp_err_t wifi_mgr_connect(const char *ssid, const char *pass);

bool wifi_mgr_is_connected(void);
bool wifi_mgr_has_saved(void);
void wifi_mgr_forget(void);

/* SSID/PASS dang luu (dung cho BLE provisioning) */
const char *wifi_mgr_get_ssid(void);
const char *wifi_mgr_get_pass(void);

#endif
#include "wifi_mgr.h"
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"

static const char *TAG = "WIFI_MGR";

#define NVS_NS "wifi"

static char s_ssid[33], s_pass[65];      /* WiFi dang dung / da luu trong NVS */
static bool s_have_saved;

static volatile bool s_connected;
static volatile bool s_scan_busy;

/* ---------------- NVS ---------------- */
static void nvs_load(void)
{
    nvs_handle_t h;
    s_have_saved = false;
    if (nvs_open(NVS_NS, NVS_READONLY, &h) != ESP_OK) return;
    size_t ls = sizeof(s_ssid), lp = sizeof(s_pass);
    if (nvs_get_str(h, "ssid", s_ssid, &ls) == ESP_OK && s_ssid[0]) {
        if (nvs_get_str(h, "pass", s_pass, &lp) != ESP_OK) s_pass[0] = 0;
        s_have_saved = true;
    }
    nvs_close(h);
}

static void nvs_save(const char *ssid, const char *pass)
{
    nvs_handle_t h;
    if (nvs_open(NVS_NS, NVS_READWRITE, &h) != ESP_OK) {
        ESP_LOGE(TAG, "Khong mo duoc NVS de luu WiFi");
        return;
    }
    nvs_set_str(h, "ssid", ssid);
    nvs_set_str(h, "pass", pass);
    nvs_commit(h);
    nvs_close(h);
}

/* ---------------- WiFi ---------------- */
static void apply_config(const char *ssid, const char *pass)
{
    wifi_config_t cfg = {0};
    strlcpy((char *)cfg.sta.ssid, ssid, sizeof(cfg.sta.ssid));
    strlcpy((char *)cfg.sta.password, pass, sizeof(cfg.sta.password));
    cfg.sta.threshold.authmode = pass[0] ? WIFI_AUTH_WPA_PSK : WIFI_AUTH_OPEN;
    esp_wifi_set_config(WIFI_IF_STA, &cfg);
}

static void wifi_event_handler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START) {
        if (s_have_saved) {
            apply_config(s_ssid, s_pass);
            esp_wifi_connect();
        }
    } else if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        s_connected = false;
        if (s_scan_busy) return;
        if (s_have_saved) {
            ESP_LOGW(TAG, "WiFi disconnect, dang thu lai...");
            esp_wifi_connect();
        }
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        s_connected = true;
        ESP_LOGI(TAG, "Da co IP");
    }
}

void wifi_mgr_init(void)
{
    nvs_load();
    ESP_LOGI(TAG, "WiFi da luu: %s", s_have_saved ? s_ssid : "(chua co)");

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

int wifi_mgr_scan(wifi_ap_record_t *out, int max)
{
    static wifi_ap_record_t tmp[24];
    s_scan_busy = true;

    if (!s_connected) esp_wifi_disconnect();

    wifi_scan_config_t sc = { .show_hidden = false, .scan_type = WIFI_SCAN_TYPE_ACTIVE };
    int count = 0;
    if (esp_wifi_scan_start(&sc, true) == ESP_OK) {
        uint16_t n = sizeof(tmp) / sizeof(tmp[0]);
        if (esp_wifi_scan_get_ap_records(&n, tmp) == ESP_OK) {
            for (int i = 0; i < n && count < max; i++) {
                if (!tmp[i].ssid[0]) continue;
                bool dup = false;
                for (int k = 0; k < count; k++) {
                    if (strcmp((char *)out[k].ssid, (char *)tmp[i].ssid) == 0) { dup = true; break; }
                }
                if (!dup) out[count++] = tmp[i];
            }
        }
    } else {
        ESP_LOGW(TAG, "Scan loi");
    }

    s_scan_busy = false;
    if (!s_connected && s_have_saved) esp_wifi_connect();
    return count;
}

/* Luu NVS NGAY khi nhan Connect, bat ke ket noi thanh cong hay khong */
esp_err_t wifi_mgr_connect(const char *ssid, const char *pass)
{
    if (!ssid || !ssid[0]) return ESP_ERR_INVALID_ARG;
    if (!pass) pass = "";

    strlcpy(s_ssid, ssid, sizeof(s_ssid));
    strlcpy(s_pass, pass, sizeof(s_pass));
    s_have_saved = true;
    nvs_save(s_ssid, s_pass);
    ESP_LOGI(TAG, "Da luu WiFi \"%s\" vao NVS", s_ssid);

    apply_config(s_ssid, s_pass);

    /* Ngat ket noi cu (neu co) roi LUON goi connect.
     * Neu dang ket noi WiFi khac, disconnect se sinh event, handler goi connect them lan nua,
     * lan goi thua nay vo hai. */
    esp_wifi_disconnect();
    esp_err_t e = esp_wifi_connect();
    ESP_LOGI(TAG, "Connect \"%s\": %s", s_ssid, esp_err_to_name(e));
    return e;
}

bool wifi_mgr_is_connected(void) { return s_connected; }
bool wifi_mgr_has_saved(void)    { return s_have_saved; }

void wifi_mgr_forget(void)
{
    nvs_handle_t h;
    if (nvs_open(NVS_NS, NVS_READWRITE, &h) == ESP_OK) {
        nvs_erase_all(h);
        nvs_commit(h);
        nvs_close(h);
    }
    s_have_saved = false;
    s_ssid[0] = s_pass[0] = 0;
    esp_wifi_disconnect();
}

const char *wifi_mgr_get_ssid(void) { return s_ssid; }
const char *wifi_mgr_get_pass(void) { return s_pass; }
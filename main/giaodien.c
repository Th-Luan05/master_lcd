#include "ui/ui.h"
#include "esp_lvgl_port.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "giaodien.h"
#include "wifi_mgr.h"
#include "esp_heap_caps.h"
#include <stdio.h>
#include <string.h>
#include "app_config.h"
#include "app_types.h"
#include "tien_ich.h"
#include "node_comm.h"
#include "automation.h"

#define SCAN_MAX 20

static wifi_ap_record_t s_aps[SCAN_MAX];
static int  s_ap_n;
static char s_sel_ssid[33];
static volatile bool s_scanning;

/* ================== Danh sach thiet bi (ScreenHome) ================== */
#define DEV_OFFLINE_MS  15000        /* node gui telemetry moi 5s */
#define DEV_REFRESH_MS  1000
/* Font mac dinh khong co dau tieng Viet. Muon hien ten co dau thi thay bang font
 * xuat tu SquareLine (them dai ky tu Vietnamese), vd &ui_font_VN14 */
LV_FONT_DECLARE(ui_font_Tiengviet14);
#define DEV_FONT        (&ui_font_Tiengviet14)

static const char *AREA_TITLE[] = {"Chưa phân phòng", "Phòng khách", "Phòng ngủ",
                                   "Bếp", "Phòng tắm", "Khác"};
static const char *TYPE_TITLE[] = {"Thiết bị", "Đèn", "Quạt", "Khác"};
static const int   AREA_ORDER[] = {1, 2, 3, 4, 5, 0};   /* "chua phan phong" xuong cuoi */
#define N_AREA_TITLE ((int)(sizeof(AREA_TITLE) / sizeof(AREA_TITLE[0])))
#define N_TYPE_TITLE ((int)(sizeof(TYPE_TITLE) / sizeof(TYPE_TITLE[0])))

typedef struct {
    uint8_t   mac[6];
    lv_obj_t *row, *name, *info, *st;
} dev_row_t;
static dev_row_t s_rows[MAX_NODES];     // <-- dong bi thieu
static void dev_update(void);   /* khai bao truoc */

#define COL_ON    lv_color_hex(0x2E9E5B)
#define COL_OFF   lv_palette_lighten(LV_PALETTE_GREY, 2)
#define COL_OFFL  lv_palette_lighten(LV_PALETTE_GREY, 3)
static int       s_row_n;
static uint32_t  s_sig;
static bool      s_sig_ok;

static uint8_t area_of(const node_t *n)
{
    return n->area < N_AREA_TITLE ? n->area : 0;
}

static bool dev_online(const node_t *n, uint32_t now)
{
    return n->last_ms != 0 && (now - n->last_ms) < DEV_OFFLINE_MS;
}

static uint32_t fnv(uint32_t h, const void *p, size_t len)
{
    const uint8_t *b = p;
    while (len--) { h ^= *b++; h *= 16777619u; }
    return h;
}

/* Chu ky "cau truc": doi khi them/bot node, doi ten/phong/loai -> ve lai danh sach */
static uint32_t dev_signature(void)
{
    uint32_t h = 2166136261u;
    for (int i = 0; i < MAX_NODES; i++) {
        const node_t *n = get_node(i);
        if (!n || !n->used) continue;
        uint8_t a = area_of(n), t = n->dtype;
        h = fnv(h, n->mac, 6);
        h = fnv(h, &a, 1);
        h = fnv(h, &t, 1);
        h = fnv(h, n->name, strnlen(n->name, NAME_LEN));
    }
    return h;
}

static void dev_row_cb(lv_event_t *e)
{
    const dev_row_t *r = lv_event_get_user_data(e);
    const node_t *n = node_find(r->mac, false);
    if (!n || !dev_online(n, now_ms())) return;           /* offline: bo qua */

    bool shown = n->want_valid ? n->want_on : (n->relay != 0);
    if (!shown && (n->flags & FLAG_OT_TRIP)) return;      /* dang khoa qua nhiet: khong cho bat */

    esp_err_t err = request_relay(r->mac, !shown);
    ESP_LOGI("UI", "Relay %02X%02X%02X -> %s (%s)", r->mac[3], r->mac[4], r->mac[5],
             !shown ? "ON" : "OFF", esp_err_to_name(err));
    dev_update();                                         /* doi mau ngay, khong cho 1 giay */
}

static void add_header(const char *text)
{
    lv_obj_t *l = lv_label_create(ui_ContainerDevice);
    lv_label_set_text(l, text);
    lv_obj_set_style_text_color(l, lv_palette_main(LV_PALETTE_BLUE), 0);
}

static void add_row(const node_t *n)
{
    dev_row_t *r = &s_rows[s_row_n++];
    memcpy(r->mac, n->mac, 6);

    char nm[NAME_LEN];
    if (n->name[0]) {
        memcpy(nm, n->name, NAME_LEN);
        nm[NAME_LEN - 1] = 0;
    } else {
        snprintf(nm, sizeof(nm), "Node %02X%02X%02X", n->mac[3], n->mac[4], n->mac[5]);
    }

    r->row = lv_obj_create(ui_ContainerDevice);
    lv_obj_set_size(r->row, lv_pct(100), 50);
    lv_obj_remove_flag(r->row, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(r->row, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_pad_all(r->row, 6, 0);
    lv_obj_set_style_radius(r->row, 8, 0);
    lv_obj_set_style_border_width(r->row, 0, 0);
    lv_obj_set_style_bg_opa(r->row, LV_OPA_COVER, 0);
    lv_obj_set_style_opa(r->row, LV_OPA_70, LV_STATE_PRESSED);   /* nhay nhe khi cham */
    lv_obj_add_event_cb(r->row, dev_row_cb, LV_EVENT_CLICKED, r);

    r->name = lv_label_create(r->row);
    lv_label_set_long_mode(r->name, LV_LABEL_LONG_DOT);
    lv_obj_set_width(r->name, lv_pct(70));
    lv_label_set_text(r->name, nm);
    lv_obj_align(r->name, LV_ALIGN_TOP_LEFT, 0, 0);

    r->info = lv_label_create(r->row);
    lv_label_set_long_mode(r->info, LV_LABEL_LONG_DOT);
    lv_obj_set_width(r->info, lv_pct(70));
    lv_label_set_text(r->info, "");
    lv_obj_align(r->info, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    r->st = lv_label_create(r->row);
    lv_label_set_text(r->st, "");
    lv_obj_align(r->st, LV_ALIGN_RIGHT_MID, 0, 0);
}

static void dev_rebuild(void)
{
    lv_obj_clean(ui_ContainerDevice);
    s_row_n = 0;

    lv_obj_set_flex_flow(ui_ContainerDevice, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(ui_ContainerDevice, 6, 0);
    lv_obj_add_flag(ui_ContainerDevice, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scroll_dir(ui_ContainerDevice, LV_DIR_VER);
    lv_obj_set_style_text_font(ui_ContainerDevice, DEV_FONT, 0);

    for (int k = 0; k < N_AREA_TITLE; k++) {
        int  a = AREA_ORDER[k];
        bool header = false;
        for (int i = 0; i < MAX_NODES; i++) {
            const node_t *n = get_node(i);
            if (!n || !n->used || area_of(n) != a) continue;
            if (!header) { add_header(AREA_TITLE[a]); header = true; }
            add_row(n);
        }
    }
    if (s_row_n == 0) {
        lv_obj_t *l = lv_label_create(ui_ContainerDevice);
        lv_label_set_text(l, "Chua co thiet bi nao");
    }
}

/* Cap nhat trang thai switch + dong thong tin, khong tao lai object */
static void dev_update(void)
{
    uint32_t now = now_ms();
    for (int i = 0; i < s_row_n; i++) {
        dev_row_t *r = &s_rows[i];
        const node_t *n = node_find(r->mac, false);
        if (!n) continue;

        bool online = dev_online(n, now);
        bool trip   = (n->flags & FLAG_OT_TRIP) != 0;
        bool warn   = (n->flags & FLAG_OT_WARN) != 0;
        /* Dang cho node xac nhan -> hien trang thai vua bam */
        bool on     = n->want_valid ? n->want_on : (n->relay != 0);

        lv_color_t bg, fg, fg2;
        const char *st;
        if (!online) {
            bg = COL_OFFL; fg = fg2 = lv_palette_main(LV_PALETTE_GREY); st = "";
        } else if (on) {
            bg = COL_ON; fg = lv_color_white(); fg2 = lv_color_white(); st = "BẬT";
        } else {
            bg = COL_OFF; fg = lv_color_black(); fg2 = lv_palette_darken(LV_PALETTE_GREY, 2); st = "TẮT";
        }

        char buf[64];
        if (!online) {
            snprintf(buf, sizeof(buf), "Offline");
        } else if (trip) {
            snprintf(buf, sizeof(buf), "QUÁ NHIỆT - đã ngắt");
            fg2 = lv_palette_main(LV_PALETTE_RED);
        } else {
            const char *ty = n->dtype < N_TYPE_TITLE ? TYPE_TITLE[n->dtype] : TYPE_TITLE[0];
            snprintf(buf, sizeof(buf), "%s | %.1f C | %.0f lux%s", ty, n->temp, n->lux,
                     warn ? " | NÓNG" : "");
            if (warn) fg2 = on ? lv_color_hex(0xFFEB3B) : lv_palette_main(LV_PALETTE_ORANGE);
        }

        lv_obj_set_style_bg_color(r->row, bg, 0);
        lv_obj_set_style_text_color(r->name, fg, 0);
        lv_obj_set_style_text_color(r->st, fg, 0);
        lv_obj_set_style_text_color(r->info, fg2, 0);
        if (strcmp(lv_label_get_text(r->info), buf) != 0) lv_label_set_text(r->info, buf);
        if (strcmp(lv_label_get_text(r->st), st) != 0)    lv_label_set_text(r->st, st);
    }
}

static void dev_refresh(bool force)
{
    uint32_t sig = dev_signature();
    if (force || !s_sig_ok || sig != s_sig) {
        dev_rebuild();
        s_sig = sig;
        s_sig_ok = true;
    }
    dev_update();
}

static void dev_timer_cb(lv_timer_t *t)
{
    if (lv_screen_active() != ui_ScreenHome) return;
    dev_refresh(false);
}

static void home_load_cb(lv_event_t *e)
{
    dev_refresh(true);
}

static void dev_ui_bind(void)
{
    lv_obj_add_event_cb(ui_ScreenHome, home_load_cb, LV_EVENT_SCREEN_LOAD_START, NULL);
    lv_timer_create(dev_timer_cb, DEV_REFRESH_MS, NULL);
}


/* Chon 1 wifi trong danh sach */
static void ap_click_cb(lv_event_t *e)
{
    int idx = (int)(intptr_t)lv_event_get_user_data(e);
    if (idx < 0 || idx >= s_ap_n) return;

    lv_strlcpy(s_sel_ssid, (char *)s_aps[idx].ssid, sizeof(s_sel_ssid));
    lv_label_set_text(ui_LabeWifiCl, s_sel_ssid);
    lv_textarea_set_text(ui_TextAreapasswwifi, "");

    lv_obj_add_flag(ui_Panelwifi, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_ContainerEnterWifi, LV_OBJ_FLAG_HIDDEN);
}

/* Goi khi DANG giu lock LVGL */
static void fill_wifi_list(void)
{
    lv_obj_clean(ui_Panelwifi);
    lv_obj_set_flex_flow(ui_Panelwifi, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(ui_Panelwifi, 6, 0);

    if (s_ap_n == 0) {
        lv_obj_t *l = lv_label_create(ui_Panelwifi);
        lv_label_set_text(l, "Khong tim thay WiFi");
        return;
    }
    for (int i = 0; i < s_ap_n; i++) {
        lv_obj_t *btn = lv_button_create(ui_Panelwifi);
        lv_obj_set_width(btn, lv_pct(100));
        lv_obj_set_height(btn, 36);
        lv_obj_add_event_cb(btn, ap_click_cb, LV_EVENT_CLICKED, (void *)(intptr_t)i);

        lv_obj_t *lb = lv_label_create(btn);
        lv_obj_set_width(lb, lv_pct(100));
        lv_label_set_long_mode(lb, LV_LABEL_LONG_DOT);
        lv_label_set_text_fmt(lb, "%s%s  (%d dBm)",
                              s_aps[i].authmode == WIFI_AUTH_OPEN ? "" : LV_SYMBOL_EYE_CLOSE " ",
                              (char *)s_aps[i].ssid, s_aps[i].rssi);
        lv_obj_align(lb, LV_ALIGN_LEFT_MID, 0, 0);
    }
}

static void scan_task(void *arg)
{
    s_ap_n = wifi_mgr_scan(s_aps, SCAN_MAX);

    if (lvgl_port_lock(0)) {
        fill_wifi_list();
        lv_obj_add_flag(ui_PanelScan, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(ui_Panelwifi, LV_OBJ_FLAG_HIDDEN);
        lvgl_port_unlock();
    }
    s_scanning = false;
    vTaskDelete(NULL);
}

/* Vao ScreenCn -> bat dau quet */
static void screen_cn_loaded_cb(lv_event_t *e)
{
    if (s_scanning) return;
    lv_obj_remove_flag(ui_PanelScan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Panelwifi, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_ContainerEnterWifi, LV_OBJ_FLAG_HIDDEN);

    s_scanning = true;
    if (xTaskCreate(scan_task, "wifi_scan", 4096, NULL, 4, NULL) != pdPASS) {
        s_scanning = false;
    }
}

/* Nhan nut Connect */
static void connect_cb(lv_event_t *e)
{
    if (!s_sel_ssid[0]) return;
    const char *pw = lv_textarea_get_text(ui_TextAreapasswwifi);
    wifi_mgr_connect(s_sel_ssid, pw);
    lv_textarea_set_text(ui_TextAreapasswwifi, "");
    lv_screen_load_anim(ui_ScreenSetting, LV_SCREEN_LOAD_ANIM_FADE_IN, 200, 0, false);
}

static void wifi_ui_bind(void)
{
    lv_textarea_set_password_mode(ui_TextAreapasswwifi, true);
    lv_textarea_set_one_line(ui_TextAreapasswwifi, true);
    lv_obj_add_event_cb(ui_ScreenCn, screen_cn_loaded_cb, LV_EVENT_SCREEN_LOADED, NULL);
    lv_obj_add_event_cb(ui_ButtonConnetWifi, connect_cb, LV_EVENT_CLICKED, NULL);
}

static void ui_watch_task(void *arg)
{
    TaskHandle_t lv = xTaskGetHandle("taskLVGL");
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(2000));

        lv_mem_monitor_t m = {0};
        bool got = lvgl_port_lock(500);       /* khong lay duoc lock trong 0.5s = dang ket */
        if (got) {
            lv_mem_monitor(&m);               /* = 0 neu LVGL dung malloc he thong */
            lvgl_port_unlock();
        }
        ESP_LOGW("UI_WATCH",
                 "lvgl_lock=%s state=%d stack_free=%u B | int_free=%u B (max blk %u) | lv_pool free=%u biggest=%u",
                 got ? "OK" : "KET",
                 lv ? (int)eTaskGetState(lv) : -1,
                 lv ? (unsigned)uxTaskGetStackHighWaterMark(lv) : 0,
                 (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
                 (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL),
                 (unsigned)m.free_size, (unsigned)m.free_biggest_size);
    }
}




void init_display(void)
{
    if (lvgl_port_lock(0)) {
        ui_init();
        wifi_ui_bind();
        dev_ui_bind();
        xTaskCreate(ui_watch_task, "ui_watch", 3072, NULL, 3, NULL);      
        lvgl_port_unlock();
    }
}

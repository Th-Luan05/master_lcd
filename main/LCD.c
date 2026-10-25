#include "LCD.h"
#include "app_config.h"

#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_check.h"
#include "esp_idf_version.h"
#include "esp_lcd_ili9341.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "esp_lcd_touch_xpt2046.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#define TAG "LCD"

#define LCD_MOSI_PIN       23
#define LCD_MISO_PIN       19
#define LCD_SCLK_PIN       18
#define LCD_CS_PIN         15
#define TOUCH_CS_PIN       5
#define TOUCH_IRQ_PIN      22
#define LCD_DC_PIN         4
#define LCD_RST_PIN        2


#define LCD_H_RES          320
#define LCD_V_RES          240
#define LCD_PIXEL_CLOCK_HZ (10 * 1000 * 1000)
#define LCD_DRAW_BUFFER_LINES 80

/* Dat x_max/y_max = 4095 de toa do touch tra ve gan nhu gia tri ADC tho (12 bit).
 * Phep hieu chinh se tu quy doi ra toa do man hinh. */
#define TOUCH_RAW_MAX      4095

/* Hieu chinh */
#define CAL_MARGIN         20     /* khoang cach tam cham toi mep man hinh (px) */
#define CAL_DOT_RADIUS     10
#define CAL_MAX_ERR_PX     25.0   /* sai so toi da cho phep sau khi fit, vuot qua -> yeu cau chạm lai */

static esp_lcd_panel_io_handle_t lcd_io;
static esp_lcd_panel_handle_t lcd_panel;
static esp_lcd_touch_handle_t touch_handle;
static lv_display_t *lvgl_display;

/* screen_x = a*rx + b*ry + c ; screen_y = d*rx + e*ry + f */
typedef struct {
    double a, b, c, d, e, f;
} touch_cal_t;

static touch_cal_t s_cal;

/* ------------------------------------------------------------------ */
/* Hardware                                                            */
/* ------------------------------------------------------------------ */

static esp_err_t lcd_hardware_init(void)
{
    ESP_RETURN_ON_ERROR(
        lcd_backlight_init(),
        TAG,
        "Backlight PWM init failed"
    );
    const spi_bus_config_t bus_config = {
        .sclk_io_num = LCD_SCLK_PIN,
        .mosi_io_num = LCD_MOSI_PIN,
        .miso_io_num = LCD_MISO_PIN,
        .quadwp_io_num = GPIO_NUM_NC,
        .quadhd_io_num = GPIO_NUM_NC,
        .max_transfer_sz = LCD_H_RES * LCD_DRAW_BUFFER_LINES * sizeof(uint16_t),
    };
    ESP_RETURN_ON_ERROR(spi_bus_initialize(SPI3_HOST, &bus_config, SPI_DMA_CH_AUTO), TAG,
                        "SPI bus init failed");

    const esp_lcd_panel_io_spi_config_t lcd_io_config = {
        .dc_gpio_num = LCD_DC_PIN,
        .cs_gpio_num = LCD_CS_PIN,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI3_HOST,
                                                  &lcd_io_config, &lcd_io), TAG,
                        "LCD panel IO inits failed");

    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = LCD_RST_PIN,
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(6, 0, 0)
        .rgb_endian = LCD_RGB_ENDIAN_BGR,
#else
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
#endif
        .bits_per_pixel = 16,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_ili9341(lcd_io, &panel_config, &lcd_panel), TAG,
                        "LCD panel init failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(lcd_panel), TAG, "LCD reset failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(lcd_panel), TAG, "LCD initialization failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_swap_xy(lcd_panel, true), TAG, "LCD axis swap failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_mirror(lcd_panel, false, false), TAG, "LCD mirror failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_disp_on_off(lcd_panel, true), TAG, "LCD enable failed");

    esp_lcd_panel_io_spi_config_t touch_io_config = ESP_LCD_TOUCH_IO_SPI_XPT2046_CONFIG(TOUCH_CS_PIN);
    touch_io_config.pclk_hz = 2 * 1000 * 1000;
    esp_lcd_panel_io_handle_t touch_io;
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI3_HOST,
                                                  &touch_io_config, &touch_io), TAG,
                        "Touch panel IO init failed");

    const esp_lcd_touch_config_t touch_config = {
        .x_max = TOUCH_RAW_MAX,
        .y_max = TOUCH_RAW_MAX,
        .rst_gpio_num = GPIO_NUM_NC,
        .int_gpio_num = TOUCH_IRQ_PIN,
        .levels = {
            .interrupt = 0,
        },
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
    };
    ESP_RETURN_ON_ERROR(esp_lcd_touch_new_spi_xpt2046(touch_io, &touch_config, &touch_handle), TAG,
                        "Touch controller init failed");
    ESP_ERROR_CHECK(lcd_set_brightness(80));
    return ESP_OK;
}

static void lcd_lvgl_init(void)
{
    const lvgl_port_display_cfg_t display_config = {
        .io_handle = lcd_io,
        .panel_handle = lcd_panel,
        .buffer_size = LCD_H_RES * LCD_DRAW_BUFFER_LINES,
        .double_buffer = true,
        .hres = LCD_H_RES,
        .vres = LCD_V_RES,
        .monochrome = false,
        .rotation = {
            .swap_xy = true,
            .mirror_x = false,
            .mirror_y = false,
        },
        .flags = {
            .buff_spiram = true,   // Bật dùng SPIRAM/PSRAM
            .buff_dma = false,     // Phải tắt DMA vì SPIRAM không dùng chung với DMA được
#if LVGL_VERSION_MAJOR >= 9
            .swap_bytes = true,
#endif
        },
    };
    lvgl_display = lvgl_port_add_disp(&display_config);

    /* KHONG goi lvgl_port_add_touch() nua.
     * Indev cam ung duoc tao trong lcd_touch_calibrate() sau khi hieu chinh xong. */
}

/* ------------------------------------------------------------------ */
/* Touch: doc toa do tho                                               */
/* ------------------------------------------------------------------ */

static bool touch_read_raw(uint16_t *x, uint16_t *y)
{
    uint16_t px = 0, py = 0, strength = 0;
    uint8_t cnt = 0;

    if (esp_lcd_touch_read_data(touch_handle) != ESP_OK) {
        return false;
    }
    /* Neu bao loi/deprecated: xem ghi chu cuoi file de dung esp_lcd_touch_get_data() */
    bool pressed = esp_lcd_touch_get_coordinates(touch_handle, &px, &py, &strength, &cnt, 1);
    if (pressed && cnt > 0) {
        *x = px;
        *y = py;
        return true;
    }
    return false;
}

/* ------------------------------------------------------------------ */
/* Toan hoc: fit affine bang binh phuong toi thieu                      */
/* ------------------------------------------------------------------ */

static double det3(const double m[3][3])
{
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
         - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
         + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

static bool solve3(const double A[3][3], const double v[3], double out[3])
{
    double d = det3(A);
    if (fabs(d) < 1.0) {
        return false; /* 4 diem suy bien (vd cham cung 1 cho) */
    }
    for (int k = 0; k < 3; k++) {
        double T[3][3];
        memcpy(T, A, sizeof(T));
        for (int r = 0; r < 3; r++) {
            T[r][k] = v[r];
        }
        out[k] = det3(T) / d;
    }
    return true;
}

/* raw[i] = {rx, ry}, scr[i] = {sx, sy}, n diem */
static bool calibration_fit(const double raw[][2], const double scr[][2], int n, touch_cal_t *cal)
{
    double sxx = 0, sxy = 0, sx = 0, syy = 0, sy = 0;
    double bx0 = 0, bx1 = 0, bx2 = 0; /* tong rx*sX, ry*sX, sX */
    double by0 = 0, by1 = 0, by2 = 0; /* tong rx*sY, ry*sY, sY */

    for (int i = 0; i < n; i++) {
        double rx = raw[i][0], ry = raw[i][1];
        sxx += rx * rx;
        sxy += rx * ry;
        sx  += rx;
        syy += ry * ry;
        sy  += ry;
        bx0 += rx * scr[i][0];
        bx1 += ry * scr[i][0];
        bx2 += scr[i][0];
        by0 += rx * scr[i][1];
        by1 += ry * scr[i][1];
        by2 += scr[i][1];
    }

    const double A[3][3] = {
        { sxx, sxy, sx },
        { sxy, syy, sy },
        { sx,  sy,  (double)n },
    };
    const double vx[3] = { bx0, bx1, bx2 };
    const double vy[3] = { by0, by1, by2 };
    double px[3], py[3];

    if (!solve3(A, vx, px) || !solve3(A, vy, py)) {
        return false;
    }

    cal->a = px[0]; cal->b = px[1]; cal->c = px[2];
    cal->d = py[0]; cal->e = py[1]; cal->f = py[2];
    return true;
}

static void calibration_apply(const touch_cal_t *cal, double rx, double ry, double *sx, double *sy)
{
    *sx = cal->a * rx + cal->b * ry + cal->c;
    *sy = cal->d * rx + cal->e * ry + cal->f;
}

/* ------------------------------------------------------------------ */
/* Bat 1 diem cham (trung binh nhieu mau)                              */
/* ------------------------------------------------------------------ */

static void capture_point(double *out_x, double *out_y)
{
    uint16_t x, y;

    /* cho cham xuong */
    while (!touch_read_raw(&x, &y)) {
        vTaskDelay(pdMS_TO_TICKS(20));
    }

    uint16_t xs[32], ys[32];
    int n = 0, miss = 0;
    xs[n] = x; ys[n] = y; n++;

    while (miss < 3 && n < 32) {
        vTaskDelay(pdMS_TO_TICKS(10));
        if (touch_read_raw(&x, &y)) {
            xs[n] = x; ys[n] = y; n++;
            miss = 0;
        } else {
            miss++;
        }
    }

    /* bo vai mau dau (luc moi cham, gia tri chua on dinh) neu du mau */
    int skip = (n > 8) ? 3 : 0;
    double sum_x = 0, sum_y = 0;
    for (int i = skip; i < n; i++) {
        sum_x += xs[i];
        sum_y += ys[i];
    }
    *out_x = sum_x / (n - skip);
    *out_y = sum_y / (n - skip);

    /* cho nha tay ra han */
    miss = 0;
    while (miss < 5) {
        if (touch_read_raw(&x, &y)) {
            miss = 0;
        } else {
            miss++;
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
    vTaskDelay(pdMS_TO_TICKS(200));
}

/* ------------------------------------------------------------------ */
/* Indev LVGL dung toa do da hieu chinh                                */
/* ------------------------------------------------------------------ */

static void touch_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    static int32_t last_x = 0, last_y = 0;
    uint16_t rx, ry;
    (void)indev;

    if (touch_read_raw(&rx, &ry)) {
        double sx, sy;
        calibration_apply(&s_cal, rx, ry, &sx, &sy);
        if (sx < 0) sx = 0;
        if (sy < 0) sy = 0;
        if (sx > LCD_H_RES - 1) sx = LCD_H_RES - 1;
        if (sy > LCD_V_RES - 1) sy = LCD_V_RES - 1;
        last_x = (int32_t)(sx + 0.5);
        last_y = (int32_t)(sy + 0.5);
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
    data->point.x = last_x;
    data->point.y = last_y;
}

static void touch_indev_register(void)
{
    if (lvgl_port_lock(0)) {
        lv_indev_t *indev = lv_indev_create();
        lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
        lv_indev_set_read_cb(indev, touch_read_cb);
        lv_indev_set_display(indev, lvgl_display);
        lvgl_port_unlock();
    }
}

/* ------------------------------------------------------------------ */
/* Man hinh hieu chinh                                                 */
/* ------------------------------------------------------------------ */

esp_err_t lcd_touch_calibrate(void)
{
    ESP_RETURN_ON_FALSE(lvgl_display && touch_handle, ESP_ERR_INVALID_STATE, TAG,
                        "Call lcd_init() first");

    const double targets[4][2] = {
        { CAL_MARGIN,              CAL_MARGIN },              /* tren-trai  */
        { LCD_H_RES - CAL_MARGIN,  CAL_MARGIN },              /* tren-phai  */
        { LCD_H_RES - CAL_MARGIN,  LCD_V_RES - CAL_MARGIN },  /* duoi-phai  */
        { CAL_MARGIN,              LCD_V_RES - CAL_MARGIN },  /* duoi-trai  */
    };

    lv_obj_t *dot = NULL;
    lv_obj_t *label = NULL;

    if (lvgl_port_lock(0)) {
        lv_obj_t *scr = lv_screen_active();
        lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
        lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

        label = lv_label_create(scr);
        lv_obj_set_style_text_color(label, lv_color_white(), 0);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

        dot = lv_obj_create(scr);
        lv_obj_remove_flag(dot, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(dot, CAL_DOT_RADIUS * 2, CAL_DOT_RADIUS * 2);
        lv_obj_set_style_radius(dot, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_pad_all(dot, 0, 0);
        lv_obj_set_style_bg_color(dot, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_bg_opa(dot, LV_OPA_COVER, 0);
        lv_obj_set_style_border_color(dot, lv_color_white(), 0);
        lv_obj_set_style_border_width(dot, 2, 0);
        lvgl_port_unlock();
    }

    double raw[4][2];

    while (true) {
        for (int i = 0; i < 4; i++) {
            if (lvgl_port_lock(0)) {
                lv_label_set_text_fmt(label, "Touch the red dot (%d/4)", i + 1);
                lv_obj_set_pos(dot,
                               (int32_t)targets[i][0] - CAL_DOT_RADIUS,
                               (int32_t)targets[i][1] - CAL_DOT_RADIUS);
                lvgl_port_unlock();
            }
            capture_point(&raw[i][0], &raw[i][1]);
            ESP_LOGI(TAG, "Point %d: raw=(%.0f, %.0f) -> target=(%.0f, %.0f)", i + 1,
                     raw[i][0], raw[i][1], targets[i][0], targets[i][1]);
        }

        touch_cal_t cal;
        bool ok = calibration_fit(raw, targets, 4, &cal);

        double max_err = 0;
        if (ok) {
            for (int i = 0; i < 4; i++) {
                double sx, sy;
                calibration_apply(&cal, raw[i][0], raw[i][1], &sx, &sy);
                double err = hypot(sx - targets[i][0], sy - targets[i][1]);
                if (err > max_err) max_err = err;
            }
            ESP_LOGI(TAG, "Calibration max error: %.1f px", max_err);
        }

        if (ok && max_err <= CAL_MAX_ERR_PX) {
            s_cal = cal;
            ESP_LOGI(TAG, "Cal: a=%.5f b=%.5f c=%.2f | d=%.5f e=%.5f f=%.2f",
                     cal.a, cal.b, cal.c, cal.d, cal.e, cal.f);
            break;
        }

        /* sai -> lam lai */
        if (lvgl_port_lock(0)) {
            lv_label_set_text(label, "Calibration failed.\nTry again.");
            lvgl_port_unlock();
        }
        vTaskDelay(pdMS_TO_TICKS(1200));
    }

    /* don dep: xoa cham tron + chu, de lai man hinh trong cho SquareLine */
    if (lvgl_port_lock(0)) {
        lv_obj_delete(dot);
        lv_obj_delete(label);
        lvgl_port_unlock();
    }

    touch_indev_register();
    return ESP_OK;
}

/* ------------------------------------------------------------------ */

esp_err_t lcd_init(void)
{
    const lvgl_port_cfg_t lvgl_config = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_RETURN_ON_ERROR(lvgl_port_init(&lvgl_config), TAG, "LVGL init failed");
    ESP_RETURN_ON_ERROR(lcd_hardware_init(), TAG, "LCD hardware init failed");
    lcd_lvgl_init();
    return ESP_OK;
}

/*
 * GHI CHU: neu ban esp_lcd_touch moi (>= 1.2 / 2.x) bao loi voi esp_lcd_touch_get_coordinates(),
 * thay noi dung touch_read_raw() bang:
 *
 *   esp_lcd_touch_point_data_t pt[1];
 *   uint8_t cnt = 0;
 *   if (esp_lcd_touch_read_data(touch_handle) != ESP_OK) return false;
 *   if (esp_lcd_touch_get_data(touch_handle, pt, &cnt, 1) == ESP_OK && cnt > 0) {
 *       *x = pt[0].x;
 *       *y = pt[0].y;
 *       return true;
 *   }
 *   return false;
 */
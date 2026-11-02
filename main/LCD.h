#ifndef LCD_H
#define LCD_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t lcd_init(void);

/* Hien 4 cham tron o 4 goc, nguoi dung cham lan luot de hieu chinh cam ung.
 * Goi sau lcd_init() va truoc ui_init(). Ham tu lock LVGL, KHONG goi khi dang giu lock. */
esp_err_t lcd_touch_calibrate(void);
void lcd_touch_cal_erase(void);

#ifdef __cplusplus
}
#endif

#endif
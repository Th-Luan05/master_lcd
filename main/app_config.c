#include "app_config.h"

#include "driver/ledc.h"

#define LCD_BK_LIGHT_PIN   32

#define LCD_PWM_FREQ_HZ    5000
#define LCD_PWM_MODE       LEDC_LOW_SPEED_MODE
#define LCD_PWM_TIMER      LEDC_TIMER_0
#define LCD_PWM_CHANNEL    LEDC_CHANNEL_0
#define LCD_PWM_RESOLUTION LEDC_TIMER_8_BIT



esp_err_t lcd_backlight_init(void)
{
    const ledc_timer_config_t timer_config = {
        .speed_mode = LCD_PWM_MODE,
        .timer_num = LCD_PWM_TIMER,
        .duty_resolution = LCD_PWM_RESOLUTION,
        .freq_hz = LCD_PWM_FREQ_HZ,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    esp_err_t err = ledc_timer_config(&timer_config);
    if (err != ESP_OK) {
        return err;
    }

    const ledc_channel_config_t channel_config = {
        .gpio_num = LCD_BK_LIGHT_PIN,
        .speed_mode = LCD_PWM_MODE,
        .channel = LCD_PWM_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LCD_PWM_TIMER,
        .duty = 255,
        .hpoint = 0,
    };

    return ledc_channel_config(&channel_config);
}

esp_err_t lcd_set_brightness(uint8_t brightness)
{
    if (brightness > 100) {
        brightness = 100;
    }

    uint32_t duty = ((uint32_t)brightness * 255U) / 100U;

    esp_err_t err = ledc_set_duty(
        LCD_PWM_MODE,
        LCD_PWM_CHANNEL,
        duty
    );

    if (err != ESP_OK) {
        return err;
    }

    return ledc_update_duty(
        LCD_PWM_MODE,
        LCD_PWM_CHANNEL
    );
}
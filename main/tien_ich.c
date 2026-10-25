#include "tien_ich.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "esp_timer.h"
#include "esp_system.h"
#include "esp_heap_caps.h"
#include "esp_sntp.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_config.h"

static const char *TAG = "TIEN_ICH";

void mac_to_str(const uint8_t *m, char *out /*13*/) {
    snprintf(out, 13, "%02X%02X%02X%02X%02X%02X", m[0], m[1], m[2], m[3], m[4], m[5]);
}

 bool parse_mac_hex(const char *s, uint8_t *out) {
    for (int i = 0; i < 6; i++) {
        char t[3] = { s[i * 2], s[i * 2 + 1], 0 };
        char *end;
        long v = strtol(t, &end, 16);
        if (*end != 0) return false;
        out[i] = (uint8_t)v;
    }
    return true;
}

 uint32_t now_ms(void) {
    return (uint32_t)(esp_timer_get_time() / 1000);
}

 bool bytes_is(const char *p, int len, const char *s) {
    return len == (int)strlen(s) && memcmp(p, s, len) == 0;
}

 void log_memory_usage(void) {
    size_t free_heap = esp_get_free_heap_size();
    size_t internal_free = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
    size_t largest_block = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);

    ESP_LOGI(TAG, "RAM heap: free=%u bytes (%u KB), min=%u bytes, internal=%u bytes, largest=%u bytes",
             (unsigned)free_heap,
             (unsigned)(free_heap / 1024),
             (unsigned)esp_get_minimum_free_heap_size(),
             (unsigned)internal_free,
             (unsigned)largest_block);

}

 void time_start(void) {
    setenv("TZ", TZ_POSIX, 1);
    tzset();
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_setservername(1, "time.google.com");
    esp_sntp_init();
}

 bool time_valid(void) {
    time_t t;
    time(&t);
    return t > 1700000000;       // đã đồng bộ NTP (sau năm 2023)
}

int lookup_idx(const void *ptr, const char **tab, int n) {
    const cJSON *item = (const cJSON *)ptr; // Ép kiểu từ void* về cJSON*
    
    if (!cJSON_IsString(item) || !item->valuestring) return -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(item->valuestring, tab[i]) == 0) return i;
    }
    return -1;
}

 void copy_name_utf8(char *dst, size_t cap, const char *src) {
    size_t n = strlen(src);
    if (n >= cap) {
        n = cap - 1;
        while (n > 0 && ((uint8_t)src[n] & 0xC0) == 0x80) n--;
    }
    memcpy(dst, src, n);
    dst[n] = 0;
}

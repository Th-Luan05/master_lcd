// tien_ich.h
#ifndef TIEN_ICH_H
#define TIEN_ICH_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "cJSON.h"
#include "proto.h"

void mac_to_str(const uint8_t *m, char *out);
bool parse_mac_hex(const char *s, uint8_t *out);
uint32_t now_ms(void);
bool bytes_is(const char *p, int len, const char *s);
void log_memory_usage(void);
void time_start(void);
bool time_valid(void);
int lookup_idx(const void *item, const char **tab, int n); // Sửa void* thay cJSON* để giảm dependency
void copy_name_utf8(char *dst, size_t cap, const char *src);


#endif
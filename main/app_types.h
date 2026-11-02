#ifndef APP_TYPES_H
#define APP_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "lwip/sockets.h"
#include "proto.h"

typedef struct {
    bool     used;
    uint8_t  mac[6];
    bool     via_udp;
    struct sockaddr_in addr;
    uint8_t  next_mac[6];
    uint8_t  hops;
    float    temp, lux;
    uint8_t  relay;
    uint8_t  flags;
    int16_t  warn_c, cut_c;
    uint32_t last_ms;
    bool     want_valid, want_on;
    uint8_t  want_tries;
    uint32_t want_ms;
    uint32_t fw;
    uint8_t  area, dtype;          // <-- them
    char     name[NAME_LEN];       // <-- them (NAME_LEN lay tu proto.h)
    bool     ota_pending, ota_check_only;
    uint8_t  ota_tries;
    uint32_t ota_ms;
} node_t;

typedef struct {
    uint8_t  used, enabled, type;
    uint8_t  action;
    uint8_t  target[6];
    uint8_t  days;
    uint8_t  src[6];
    uint8_t  metric, op, revert;
    int16_t  at_min;
    int16_t  win_from, win_to;
    float    value, hyst;
} rule_t;

typedef struct { bool active; int32_t last_key; } rule_rt_t;

typedef struct {
    bool     is_udp;
    uint8_t  from_mac[6];
    struct sockaddr_in from;
    uint8_t  data[sizeof(pkt_t)];
} rx_item_t;

extern const char *AREAS[];
extern const char *TYPES[];
extern const int N_AREAS;
extern const int N_TYPES;

#endif
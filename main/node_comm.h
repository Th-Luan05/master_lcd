#ifndef NODE_COMM_H
#define NODE_COMM_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "app_types.h"

void espnow_start(void);
void start_scan(void);
node_t *node_find(const uint8_t *mac, bool create);
node_t *get_node(int idx);
esp_err_t send_to_node(const uint8_t *mac, const pkt_t *p);
esp_err_t send_relay_cmd(const uint8_t *mac, bool on);
void handle_config(const uint8_t *mac, const char *data, int dl);
void init_cmd_hdr(pkt_t *p, uint8_t type, const uint8_t *dst);
const uint8_t *get_my_mac(void);

#endif
// ota_app.h
#ifndef OTA_APP_H
#define OTA_APP_H

#include "app_types.h"

void handle_ota_cmd(const char *data, int dl);
void handle_ota_status(const pkt_t *p);
void ota_retry(node_t *n, uint32_t now);

#endif
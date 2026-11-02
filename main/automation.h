#ifndef AUTOMATION_H
#define AUTOMATION_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

void automation_init(void);
void handle_rule_set(int id, const char *data, int dl);
void handle_safety(const uint8_t *mac, const char *data, int dl);
esp_err_t request_relay(const uint8_t *mac, bool on);
void publish_all_rules(void);

#endif
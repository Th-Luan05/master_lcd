#ifndef MQTT_APP_H
#define MQTT_APP_H

void mqtt_app_start(void);
void mqtt_pub(const char *topic, const char *payload);
void mqtt_pub_r(const char *topic, const char *payload, int retain);

#endif
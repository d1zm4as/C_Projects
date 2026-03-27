#ifndef MQTT_SIMPLE_H
#define MQTT_SIMPLE_H

#include <stddef.h>
#include <stdint.h>

size_t mqtt_encode_connect(const char *client_id, uint16_t keep_alive,
                           uint8_t *out, size_t out_size);

size_t mqtt_encode_pingreq(uint8_t *out, size_t out_size);

#endif

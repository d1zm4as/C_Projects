#ifndef ZIGBEE_APS_H
#define ZIGBEE_APS_H

#include <stddef.h>
#include <stdint.h>

#define ZIGBEE_APS_MAX_PAYLOAD 64u

/* Simplified APS data frame (not a full Zigbee stack). */
typedef struct {
    uint16_t profile_id;
    uint16_t cluster_id;
    uint8_t src_endpoint;
    uint8_t dst_endpoint;
    uint8_t payload[ZIGBEE_APS_MAX_PAYLOAD];
    uint8_t payload_len;
} zigbee_aps_frame_t;

size_t zigbee_aps_pack(const zigbee_aps_frame_t *frame, uint8_t *out, size_t out_size);
int zigbee_aps_unpack(const uint8_t *data, size_t len, zigbee_aps_frame_t *out_frame);

#endif

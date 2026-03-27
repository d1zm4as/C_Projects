#include "zigbee_aps.h"
#include "../../common/hex_dump.h"
#include <stdio.h>

int main(void)
{
    zigbee_aps_frame_t frame;
    zigbee_aps_frame_t decoded;
    uint8_t buffer[128];
    size_t len;

    frame.profile_id = 0x0104;  /* Home Automation */
    frame.cluster_id = 0x0006;  /* On/Off cluster */
    frame.src_endpoint = 0x01;
    frame.dst_endpoint = 0x0A;
    frame.payload_len = 1;
    frame.payload[0] = 0x01; /* ZCL: On */

    len = zigbee_aps_pack(&frame, buffer, sizeof(buffer));
    if (len == 0) {
        printf("Failed to pack Zigbee APS frame\n");
        return 1;
    }

    printf("APS frame (%zu bytes):\n", len);
    hex_dump(stdout, buffer, len, 16);

    if (!zigbee_aps_unpack(buffer, len, &decoded)) {
        printf("Failed to unpack Zigbee APS frame\n");
        return 1;
    }

    printf("Decoded: profile=0x%04X cluster=0x%04X src_ep=%u dst_ep=%u payload=", 
           decoded.profile_id, decoded.cluster_id,
           decoded.src_endpoint, decoded.dst_endpoint);
    for (size_t i = 0; i < decoded.payload_len; ++i) {
        printf("%02X ", decoded.payload[i]);
    }
    printf("\n");

    return 0;
}

#include "can_frame.h"
#include "../../common/hex_dump.h"
#include <stdio.h>

int main(void)
{
    can_frame_t frame;
    can_frame_t decoded;
    uint8_t buffer[32];
    size_t len;

    frame.id = 0x123;
    frame.dlc = 4;
    frame.data[0] = 0xDE;
    frame.data[1] = 0xAD;
    frame.data[2] = 0xBE;
    frame.data[3] = 0xEF;

    len = can_frame_pack(&frame, buffer, sizeof(buffer));
    if (len == 0) {
        printf("Failed to pack CAN frame\n");
        return 1;
    }

    printf("Packed frame (%zu bytes):\n", len);
    hex_dump(stdout, buffer, len, 16);

    if (!can_frame_unpack(buffer, len, &decoded)) {
        printf("Failed to unpack CAN frame\n");
        return 1;
    }

    printf("Decoded: ID=0x%03X DLC=%u DATA=", decoded.id, decoded.dlc);
    for (size_t i = 0; i < decoded.dlc; ++i) {
        printf("%02X ", decoded.data[i]);
    }
    printf("\n");

    return 0;
}

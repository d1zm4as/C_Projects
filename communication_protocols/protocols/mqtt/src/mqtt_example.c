#include "mqtt_simple.h"
#include "../../common/hex_dump.h"
#include <stdio.h>

int main(void)
{
    uint8_t buffer[256];
    size_t len;

    len = mqtt_encode_connect("client-01", 60, buffer, sizeof(buffer));
    if (len == 0) {
        printf("Failed to encode CONNECT\n");
        return 1;
    }

    printf("CONNECT packet (%zu bytes):\n", len);
    hex_dump(stdout, buffer, len, 16);

    len = mqtt_encode_pingreq(buffer, sizeof(buffer));
    if (len == 0) {
        printf("Failed to encode PINGREQ\n");
        return 1;
    }

    printf("PINGREQ packet (%zu bytes):\n", len);
    hex_dump(stdout, buffer, len, 16);

    return 0;
}

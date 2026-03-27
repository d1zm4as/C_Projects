#include "spi_protocol.h"
#include <stdio.h>

static void print_packet(const spi_packet_t *pkt)
{
    printf("CMD=0x%02X LEN=%u DATA=", pkt->cmd, pkt->length);
    for (size_t i = 0; i < pkt->length; ++i) {
        printf("%02X ", pkt->payload[i]);
    }
    printf("\n");
}

int main(void)
{
    const uint8_t payload[] = { 0x10, 0x20, 0x30 };
    uint8_t buffer[128];
    spi_packet_t decoded;
    size_t len;

    len = spi_packet_encode(0x01, payload, sizeof(payload), buffer, sizeof(buffer));
    if (len == 0) {
        printf("Failed to encode SPI packet\n");
        return 1;
    }

    if (!spi_packet_decode(buffer, len, &decoded)) {
        printf("Failed to decode SPI packet\n");
        return 1;
    }

    printf("Decoded packet: ");
    print_packet(&decoded);

    return 0;
}

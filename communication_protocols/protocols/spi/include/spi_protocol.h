#ifndef SPI_PROTOCOL_H
#define SPI_PROTOCOL_H

#include <stddef.h>
#include <stdint.h>

#define SPI_PKT_SYNC 0xA5u
#define SPI_PKT_MAX_PAYLOAD 64u

typedef struct {
    uint8_t cmd;
    uint8_t length;
    uint8_t payload[SPI_PKT_MAX_PAYLOAD];
} spi_packet_t;

size_t spi_packet_encode(uint8_t cmd, const uint8_t *payload, size_t len,
                         uint8_t *out, size_t out_size);

int spi_packet_decode(const uint8_t *data, size_t len, spi_packet_t *out_pkt);

#endif

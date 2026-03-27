#include "spi_protocol.h"

static uint8_t spi_checksum(const uint8_t *data, size_t len)
{
    uint8_t sum = 0;
    for (size_t i = 0; i < len; ++i) {
        sum ^= data[i];
    }
    return sum;
}

size_t spi_packet_encode(uint8_t cmd, const uint8_t *payload, size_t len,
                         uint8_t *out, size_t out_size)
{
    size_t needed;
    uint8_t checksum;

    if (!out || (!payload && len > 0) || len > SPI_PKT_MAX_PAYLOAD) {
        return 0;
    }

    needed = 1 + 1 + 1 + len + 1;
    if (out_size < needed) {
        return 0;
    }

    out[0] = SPI_PKT_SYNC;
    out[1] = cmd;
    out[2] = (uint8_t)len;
    for (size_t i = 0; i < len; ++i) {
        out[3 + i] = payload[i];
    }

    checksum = spi_checksum(&out[1], 2 + len);
    out[3 + len] = checksum;

    return needed;
}

int spi_packet_decode(const uint8_t *data, size_t len, spi_packet_t *out_pkt)
{
    uint8_t checksum;

    if (!data || !out_pkt || len < 4) {
        return 0;
    }

    if (data[0] != SPI_PKT_SYNC) {
        return 0;
    }

    out_pkt->cmd = data[1];
    out_pkt->length = data[2];

    if (out_pkt->length > SPI_PKT_MAX_PAYLOAD) {
        return 0;
    }

    if (len != (size_t)(4 + out_pkt->length)) {
        return 0;
    }

    for (size_t i = 0; i < out_pkt->length; ++i) {
        out_pkt->payload[i] = data[3 + i];
    }

    checksum = spi_checksum(&data[1], 2 + out_pkt->length);
    if (checksum != data[3 + out_pkt->length]) {
        return 0;
    }

    return 1;
}

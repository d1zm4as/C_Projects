#include "crc16.h"

uint16_t crc16_ibm(const uint8_t *data, size_t len)
{
    uint16_t crc = 0xFFFFu;
    size_t i;

    if (!data) {
        return crc;
    }

    for (i = 0; i < len; ++i) {
        uint8_t byte = data[i];
        int bit;

        crc ^= (uint16_t)byte;
        for (bit = 0; bit < 8; ++bit) {
            if (crc & 0x0001u) {
                crc = (uint16_t)((crc >> 1) ^ 0xA001u);
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}

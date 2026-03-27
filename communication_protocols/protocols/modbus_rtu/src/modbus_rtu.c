#include "modbus_rtu.h"
#include "../../common/crc16.h"

static void modbus_append_crc(uint8_t *frame, size_t len)
{
    uint16_t crc = crc16_ibm(frame, len);
    frame[len] = (uint8_t)(crc & 0xFFu);
    frame[len + 1] = (uint8_t)((crc >> 8) & 0xFFu);
}

static int modbus_check_crc(const uint8_t *frame, size_t len)
{
    uint16_t crc;
    uint16_t expected;

    if (len < 2) {
        return 0;
    }

    crc = crc16_ibm(frame, len - 2);
    expected = (uint16_t)(frame[len - 2] | (frame[len - 1] << 8));
    return crc == expected;
}

size_t modbus_rtu_build_read_holding(uint8_t slave, uint16_t start_addr,
                                     uint16_t quantity, uint8_t *out,
                                     size_t out_size)
{
    if (!out || out_size < 8) {
        return 0;
    }

    out[0] = slave;
    out[1] = 0x03; /* Read Holding Registers */
    out[2] = (uint8_t)(start_addr >> 8);
    out[3] = (uint8_t)(start_addr & 0xFFu);
    out[4] = (uint8_t)(quantity >> 8);
    out[5] = (uint8_t)(quantity & 0xFFu);

    modbus_append_crc(out, 6);
    return 8;
}

int modbus_rtu_parse_read_holding_response(const uint8_t *frame, size_t len,
                                           uint8_t *out_bytes, size_t out_size,
                                           size_t *out_len)
{
    uint8_t byte_count;

    if (!frame || !out_bytes || !out_len || len < 5) {
        return 0;
    }

    if (!modbus_check_crc(frame, len)) {
        return 0;
    }

    if (frame[1] != 0x03) {
        return 0;
    }

    byte_count = frame[2];
    if ((size_t)(byte_count + 5) != len || byte_count > out_size) {
        return 0;
    }

    for (size_t i = 0; i < byte_count; ++i) {
        out_bytes[i] = frame[3 + i];
    }

    *out_len = byte_count;
    return 1;
}

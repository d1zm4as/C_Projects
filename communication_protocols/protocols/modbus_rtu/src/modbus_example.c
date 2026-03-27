#include "modbus_rtu.h"
#include "../../common/hex_dump.h"
#include "../../common/crc16.h"
#include <stdio.h>

static size_t build_mock_response(uint8_t slave, const uint8_t *payload,
                                  size_t payload_len, uint8_t *out,
                                  size_t out_size)
{
    if (!out || out_size < payload_len + 5) {
        return 0;
    }

    out[0] = slave;
    out[1] = 0x03;
    out[2] = (uint8_t)payload_len;

    for (size_t i = 0; i < payload_len; ++i) {
        out[3 + i] = payload[i];
    }

    /* CRC */
    uint16_t crc = crc16_ibm(out, 3 + payload_len);
    out[3 + payload_len] = (uint8_t)(crc & 0xFFu);
    out[4 + payload_len] = (uint8_t)((crc >> 8) & 0xFFu);

    return payload_len + 5;
}

int main(void)
{
    uint8_t request[8];
    size_t req_len;
    uint8_t response[64];
    size_t resp_len;
    uint8_t data_bytes[32];
    size_t data_len = 0;
    const uint8_t sample_payload[] = { 0x00, 0x2A, 0x01, 0x02 };

    req_len = modbus_rtu_build_read_holding(0x01, 0x0000, 2, request, sizeof(request));
    if (req_len == 0) {
        printf("Failed to build request\n");
        return 1;
    }

    printf("Request frame (%zu bytes):\n", req_len);
    hex_dump(stdout, request, req_len, 16);

    resp_len = build_mock_response(0x01, sample_payload, sizeof(sample_payload),
                                   response, sizeof(response));
    if (resp_len == 0) {
        printf("Failed to build mock response\n");
        return 1;
    }

    printf("Response frame (%zu bytes):\n", resp_len);
    hex_dump(stdout, response, resp_len, 16);

    if (!modbus_rtu_parse_read_holding_response(response, resp_len,
                                                data_bytes, sizeof(data_bytes),
                                                &data_len)) {
        printf("Failed to parse response\n");
        return 1;
    }

    printf("Parsed data (%zu bytes): ", data_len);
    for (size_t i = 0; i < data_len; ++i) {
        printf("%02X ", data_bytes[i]);
    }
    printf("\n");

    return 0;
}

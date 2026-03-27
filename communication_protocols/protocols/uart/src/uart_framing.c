#include "uart_framing.h"
#include "../../common/crc16.h"

void uart_frame_parser_init(uart_frame_parser_t *parser)
{
    if (!parser) {
        return;
    }

    parser->state = UART_PARSER_WAIT_SOF;
    parser->length = 0;
    parser->index = 0;
    parser->crc = 0;
}

size_t uart_frame_encode(const uint8_t *payload, size_t len,
                         uint8_t *out, size_t out_size)
{
    uint16_t crc;
    size_t needed;

    if (!payload || !out || len > UART_FRAME_MAX_PAYLOAD) {
        return 0;
    }

    needed = 1 + 1 + len + 2;
    if (out_size < needed) {
        return 0;
    }

    out[0] = UART_FRAME_SOF;
    out[1] = (uint8_t)len;
    for (size_t i = 0; i < len; ++i) {
        out[2 + i] = payload[i];
    }

    crc = crc16_ibm(payload, len);
    out[2 + len] = (uint8_t)(crc & 0xFFu);
    out[2 + len + 1] = (uint8_t)((crc >> 8) & 0xFFu);

    return needed;
}

static void uart_parser_reset(uart_frame_parser_t *parser)
{
    parser->state = UART_PARSER_WAIT_SOF;
    parser->length = 0;
    parser->index = 0;
    parser->crc = 0;
}

int uart_frame_parser_feed(uart_frame_parser_t *parser, uint8_t byte,
                           uint8_t *out_payload, size_t out_size,
                           size_t *out_len)
{
    if (!parser || !out_payload || !out_len) {
        return 0;
    }

    switch (parser->state) {
    case UART_PARSER_WAIT_SOF:
        if (byte == UART_FRAME_SOF) {
            parser->state = UART_PARSER_WAIT_LEN;
        }
        break;
    case UART_PARSER_WAIT_LEN:
        parser->length = byte;
        parser->index = 0;
        if (parser->length > UART_FRAME_MAX_PAYLOAD) {
            uart_parser_reset(parser);
            break;
        }
        parser->state = (parser->length == 0) ? UART_PARSER_WAIT_CRC0
                                              : UART_PARSER_WAIT_PAYLOAD;
        break;
    case UART_PARSER_WAIT_PAYLOAD:
        parser->payload[parser->index++] = byte;
        if (parser->index >= parser->length) {
            parser->state = UART_PARSER_WAIT_CRC0;
        }
        break;
    case UART_PARSER_WAIT_CRC0:
        parser->crc = byte;
        parser->state = UART_PARSER_WAIT_CRC1;
        break;
    case UART_PARSER_WAIT_CRC1: {
        uint16_t expected_crc;
        parser->crc |= (uint16_t)byte << 8;
        expected_crc = crc16_ibm(parser->payload, parser->length);
        if (expected_crc == parser->crc && out_size >= parser->length) {
            for (size_t i = 0; i < parser->length; ++i) {
                out_payload[i] = parser->payload[i];
            }
            *out_len = parser->length;
            uart_parser_reset(parser);
            return 1;
        }
        uart_parser_reset(parser);
        break;
    }
    default:
        uart_parser_reset(parser);
        break;
    }

    return 0;
}

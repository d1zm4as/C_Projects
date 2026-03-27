#ifndef UART_FRAMING_H
#define UART_FRAMING_H

#include <stddef.h>
#include <stdint.h>

#define UART_FRAME_SOF 0x7Eu
#define UART_FRAME_MAX_PAYLOAD 255u

typedef enum {
    UART_PARSER_WAIT_SOF = 0,
    UART_PARSER_WAIT_LEN,
    UART_PARSER_WAIT_PAYLOAD,
    UART_PARSER_WAIT_CRC0,
    UART_PARSER_WAIT_CRC1
} uart_parser_state_t;

typedef struct {
    uart_parser_state_t state;
    uint8_t payload[UART_FRAME_MAX_PAYLOAD];
    uint8_t length;
    uint8_t index;
    uint16_t crc;
} uart_frame_parser_t;

void uart_frame_parser_init(uart_frame_parser_t *parser);

size_t uart_frame_encode(const uint8_t *payload, size_t len,
                         uint8_t *out, size_t out_size);

int uart_frame_parser_feed(uart_frame_parser_t *parser, uint8_t byte,
                           uint8_t *out_payload, size_t out_size,
                           size_t *out_len);

#endif

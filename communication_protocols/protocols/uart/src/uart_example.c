#include "uart_framing.h"
#include "../../common/hex_dump.h"
#include <stdio.h>

int main(void)
{
    const uint8_t payload[] = { 'H', 'e', 'l', 'l', 'o' };
    uint8_t frame[64];
    uint8_t decoded[UART_FRAME_MAX_PAYLOAD];
    size_t frame_len;
    size_t decoded_len = 0;
    uart_frame_parser_t parser;

    uart_frame_parser_init(&parser);
    frame_len = uart_frame_encode(payload, sizeof(payload), frame, sizeof(frame));

    printf("Encoded frame (%zu bytes):\n", frame_len);
    hex_dump(stdout, frame, frame_len, 16);

    for (size_t i = 0; i < frame_len; ++i) {
        if (uart_frame_parser_feed(&parser, frame[i], decoded, sizeof(decoded), &decoded_len)) {
            printf("Decoded payload (%zu bytes): ", decoded_len);
            for (size_t j = 0; j < decoded_len; ++j) {
                fputc(decoded[j], stdout);
            }
            printf("\n");
        }
    }

    return 0;
}

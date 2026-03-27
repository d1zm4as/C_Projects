#include "mqtt_simple.h"
#include <string.h>

static size_t mqtt_encode_remaining_length(uint32_t value, uint8_t *out, size_t out_size)
{
    size_t i = 0;

    do {
        if (i >= out_size) {
            return 0;
        }
        uint8_t byte = (uint8_t)(value % 128);
        value /= 128;
        if (value > 0) {
            byte |= 0x80u;
        }
        out[i++] = byte;
    } while (value > 0);

    return i;
}

size_t mqtt_encode_connect(const char *client_id, uint16_t keep_alive,
                           uint8_t *out, size_t out_size)
{
    const char *proto = "MQTT";
    size_t client_len;
    size_t remaining_length;
    size_t rl_bytes;
    size_t index = 0;

    if (!client_id || !out) {
        return 0;
    }

    client_len = strlen(client_id);
    if (client_len > 0xFFFFu) {
        return 0;
    }

    remaining_length = 10 + 2 + client_len;

    out[index++] = 0x10; /* CONNECT */
    rl_bytes = mqtt_encode_remaining_length((uint32_t)remaining_length, &out[index],
                                            out_size - index);
    if (rl_bytes == 0) {
        return 0;
    }
    index += rl_bytes;

    if (out_size < index + remaining_length) {
        return 0;
    }

    /* Protocol Name */
    out[index++] = 0x00;
    out[index++] = 0x04;
    memcpy(&out[index], proto, 4);
    index += 4;

    out[index++] = 0x04; /* Protocol Level 4 */
    out[index++] = 0x02; /* Clean Session */
    out[index++] = (uint8_t)(keep_alive >> 8);
    out[index++] = (uint8_t)(keep_alive & 0xFFu);

    /* Client ID */
    out[index++] = (uint8_t)(client_len >> 8);
    out[index++] = (uint8_t)(client_len & 0xFFu);
    memcpy(&out[index], client_id, client_len);
    index += client_len;

    return index;
}

size_t mqtt_encode_pingreq(uint8_t *out, size_t out_size)
{
    if (!out || out_size < 2) {
        return 0;
    }

    out[0] = 0xC0;
    out[1] = 0x00;
    return 2;
}

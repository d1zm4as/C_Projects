#include "zigbee_aps.h"

static void write_le16(uint8_t *out, uint16_t value)
{
    out[0] = (uint8_t)(value & 0xFFu);
    out[1] = (uint8_t)((value >> 8) & 0xFFu);
}

static uint16_t read_le16(const uint8_t *data)
{
    return (uint16_t)(data[0] | (data[1] << 8));
}

size_t zigbee_aps_pack(const zigbee_aps_frame_t *frame, uint8_t *out, size_t out_size)
{
    size_t needed;

    if (!frame || !out || frame->payload_len > ZIGBEE_APS_MAX_PAYLOAD) {
        return 0;
    }

    /* Format: dst_ep | cluster_id (LE) | profile_id (LE) | src_ep | payload */
    needed = 1 + 2 + 2 + 1 + frame->payload_len;
    if (out_size < needed) {
        return 0;
    }

    out[0] = frame->dst_endpoint;
    write_le16(&out[1], frame->cluster_id);
    write_le16(&out[3], frame->profile_id);
    out[5] = frame->src_endpoint;

    for (size_t i = 0; i < frame->payload_len; ++i) {
        out[6 + i] = frame->payload[i];
    }

    return needed;
}

int zigbee_aps_unpack(const uint8_t *data, size_t len, zigbee_aps_frame_t *out_frame)
{
    if (!data || !out_frame || len < 6) {
        return 0;
    }

    out_frame->dst_endpoint = data[0];
    out_frame->cluster_id = read_le16(&data[1]);
    out_frame->profile_id = read_le16(&data[3]);
    out_frame->src_endpoint = data[5];

    out_frame->payload_len = (uint8_t)(len - 6);
    if (out_frame->payload_len > ZIGBEE_APS_MAX_PAYLOAD) {
        return 0;
    }

    for (size_t i = 0; i < out_frame->payload_len; ++i) {
        out_frame->payload[i] = data[6 + i];
    }

    return 1;
}

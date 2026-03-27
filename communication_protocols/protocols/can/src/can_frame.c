#include "can_frame.h"

size_t can_frame_pack(const can_frame_t *frame, uint8_t *out, size_t out_size)
{
    size_t needed;
    uint16_t id;

    if (!frame || !out || frame->dlc > CAN_MAX_DATA) {
        return 0;
    }

    needed = 2 + 1 + frame->dlc;
    if (out_size < needed) {
        return 0;
    }

    id = (uint16_t)(frame->id & 0x07FFu);
    out[0] = (uint8_t)((id >> 8) & 0xFFu);
    out[1] = (uint8_t)(id & 0xFFu);
    out[2] = frame->dlc;

    for (size_t i = 0; i < frame->dlc; ++i) {
        out[3 + i] = frame->data[i];
    }

    return needed;
}

int can_frame_unpack(const uint8_t *data, size_t len, can_frame_t *out_frame)
{
    uint16_t id;

    if (!data || !out_frame || len < 3) {
        return 0;
    }

    id = (uint16_t)((data[0] << 8) | data[1]);
    out_frame->id = (uint16_t)(id & 0x07FFu);
    out_frame->dlc = data[2];

    if (out_frame->dlc > CAN_MAX_DATA || len != (size_t)(3 + out_frame->dlc)) {
        return 0;
    }

    for (size_t i = 0; i < out_frame->dlc; ++i) {
        out_frame->data[i] = data[3 + i];
    }

    return 1;
}

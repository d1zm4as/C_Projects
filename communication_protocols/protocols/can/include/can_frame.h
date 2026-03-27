#ifndef CAN_FRAME_H
#define CAN_FRAME_H

#include <stddef.h>
#include <stdint.h>

#define CAN_MAX_DATA 8u

/* Standard 11-bit ID frame, user-space serialization example. */
typedef struct {
    uint16_t id;
    uint8_t dlc;
    uint8_t data[CAN_MAX_DATA];
} can_frame_t;

size_t can_frame_pack(const can_frame_t *frame, uint8_t *out, size_t out_size);
int can_frame_unpack(const uint8_t *data, size_t len, can_frame_t *out_frame);

#endif

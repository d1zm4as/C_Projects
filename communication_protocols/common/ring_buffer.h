#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t *buffer;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t size;
} ring_buffer_t;

void ring_buffer_init(ring_buffer_t *rb, uint8_t *storage, size_t capacity);
size_t ring_buffer_write(ring_buffer_t *rb, const uint8_t *data, size_t len);
size_t ring_buffer_read(ring_buffer_t *rb, uint8_t *out, size_t len);
size_t ring_buffer_available(const ring_buffer_t *rb);
size_t ring_buffer_free(const ring_buffer_t *rb);

#ifdef __cplusplus
}
#endif

#endif

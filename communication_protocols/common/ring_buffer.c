#include "ring_buffer.h"

void ring_buffer_init(ring_buffer_t *rb, uint8_t *storage, size_t capacity)
{
    if (!rb || !storage || capacity == 0) {
        return;
    }

    rb->buffer = storage;
    rb->capacity = capacity;
    rb->head = 0;
    rb->tail = 0;
    rb->size = 0;
}

size_t ring_buffer_write(ring_buffer_t *rb, const uint8_t *data, size_t len)
{
    size_t written = 0;

    if (!rb || !data || rb->capacity == 0) {
        return 0;
    }

    while (written < len && rb->size < rb->capacity) {
        rb->buffer[rb->head] = data[written];
        rb->head = (rb->head + 1) % rb->capacity;
        rb->size++;
        written++;
    }

    return written;
}

size_t ring_buffer_read(ring_buffer_t *rb, uint8_t *out, size_t len)
{
    size_t read = 0;

    if (!rb || !out || rb->capacity == 0) {
        return 0;
    }

    while (read < len && rb->size > 0) {
        out[read] = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % rb->capacity;
        rb->size--;
        read++;
    }

    return read;
}

size_t ring_buffer_available(const ring_buffer_t *rb)
{
    if (!rb) {
        return 0;
    }

    return rb->size;
}

size_t ring_buffer_free(const ring_buffer_t *rb)
{
    if (!rb) {
        return 0;
    }

    return rb->capacity - rb->size;
}

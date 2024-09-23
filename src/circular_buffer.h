#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Replace this type with the one you need.
typedef uint8_t BufferType_t;

typedef struct {
    BufferType_t* p_buffer;
    size_t size;
    int readPos;
    int writePos;
    bool isFull;
} CircularBuffer_t;

void circular_buffer_init(CircularBuffer_t* p_cb, BufferType_t* p_buffer, size_t size);
void circular_buffer_write(CircularBuffer_t* p_cb, BufferType_t data);
BufferType_t circular_buffer_read(CircularBuffer_t* p_cb);
size_t circular_buffer_length(CircularBuffer_t* p_cb);

#endif
#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t* p_buffer;
    uint8_t size;
    uint8_t readPos;
    uint8_t writePos;
    bool isFull;
} CircularBuffer_t;

void circular_buffer_init(CircularBuffer_t* p_cb, uint8_t size);
void circular_buffer_write(CircularBuffer_t* p_cb, uint8_t data);
uint8_t circular_buffer_read(CircularBuffer_t* p_cb);
uint8_t circular_buffer_length(CircularBuffer_t* p_cb);
#endif
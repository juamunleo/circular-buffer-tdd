#include "circular_buffer.h"

static void addAvoidingOverflow(uint8_t* position, uint8_t size) {
    if(*position < (size - 1)) {
        *position += 1;
    } else {
        *position = 0;
    }
}

void circular_buffer_init(CircularBuffer_t* p_cb, uint8_t size) {
    p_cb->size = size;
    p_cb->readPos = 0;
    p_cb->writePos = 0;
}

void circular_buffer_write(CircularBuffer_t* p_cb, uint8_t data) {
    if(p_cb->isFull) return;

    p_cb->p_buffer[p_cb->writePos] = data;
    addAvoidingOverflow(&p_cb->writePos, p_cb->size);
    p_cb->isFull = p_cb->writePos == p_cb->readPos;
}

uint8_t circular_buffer_read(CircularBuffer_t* p_cb) {
    if(circular_buffer_length(p_cb) == 0) return 0;

    uint8_t data = p_cb->p_buffer[p_cb->readPos];
    addAvoidingOverflow(&p_cb->readPos, p_cb->size);
    p_cb->isFull = false;
    return data;
}

uint8_t circular_buffer_length(CircularBuffer_t* p_cb) {
    uint8_t length;
    if(p_cb->readPos < p_cb->writePos) {
        length = p_cb->writePos - p_cb->readPos;
    } else if(p_cb->readPos > p_cb->writePos) {
        length = (p_cb->size - p_cb->readPos) + p_cb->writePos;
    } else if(p_cb->readPos == p_cb->writePos && p_cb->isFull) {
        length = p_cb->size;
    } else {
        length = 0;
    }
    return length;
}
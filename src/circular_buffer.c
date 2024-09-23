#include "circular_buffer.h"

static void addAvoidingOverflow(int* position, size_t size) {
    if(*position < (size - 1)) {
        *position += 1;
    } else {
        *position = 0;
    }
}

void circular_buffer_init(CircularBuffer_t* p_cb, BufferType_t* p_buffer, size_t size) {
    p_cb->p_buffer = p_buffer;
    p_cb->size = size;
    p_cb->readPos = 0;
    p_cb->writePos = 0;
    p_cb->isFull = false;
}

void circular_buffer_write(CircularBuffer_t* p_cb, BufferType_t data) {
    if(p_cb->isFull) return;

    p_cb->p_buffer[p_cb->writePos] = data;
    addAvoidingOverflow(&p_cb->writePos, p_cb->size);
    p_cb->isFull = p_cb->writePos == p_cb->readPos;
}

BufferType_t circular_buffer_read(CircularBuffer_t* p_cb) {
    if(circular_buffer_length(p_cb) == 0) return 0;

    BufferType_t data = p_cb->p_buffer[p_cb->readPos];
    addAvoidingOverflow(&p_cb->readPos, p_cb->size);
    p_cb->isFull = false;
    return data;
}

size_t circular_buffer_length(CircularBuffer_t* p_cb) {
    size_t length;
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
#include "unity_fixture.h"
#include "circular_buffer.h"

TEST_GROUP(CircularBuffer);

static BufferType_t buffer[3] = {0};
static CircularBuffer_t cb;

TEST_SETUP(CircularBuffer) {
    for(uint_fast8_t i=0; i<sizeof(buffer)/sizeof(BufferType_t); i++) {
        buffer[i] = 0;
    }
    circular_buffer_init(&cb, buffer, sizeof(buffer)/sizeof(BufferType_t));
}

TEST_TEAR_DOWN(CircularBuffer) {

}

TEST(CircularBuffer, Initialize) {
    cb = (CircularBuffer_t) {
        .p_buffer = (BufferType_t[]) {0xFF, 0xFF, 0xFF},
        .size = 0xFF,
        .readPos = 0xFF,
        .writePos = 0xFF,
        .isFull = true
    };
    circular_buffer_init(&cb, buffer, sizeof(buffer)/sizeof(BufferType_t));
    TEST_ASSERT_EQUAL(3, cb.size);
    TEST_ASSERT_EQUAL(0, cb.readPos);
    TEST_ASSERT_EQUAL(0, cb.writePos);
    TEST_ASSERT_EQUAL(false, cb.isFull);
}

TEST(CircularBuffer, WriteOne) {
    circular_buffer_write(&cb, 1);
    TEST_ASSERT_EQUAL(1, cb.p_buffer[0]);
}


TEST(CircularBuffer, ReadOne) {
    circular_buffer_write(&cb, 1);
    uint8_t data = circular_buffer_read(&cb);
    TEST_ASSERT_EQUAL(1, data);
}

TEST(CircularBuffer, WritePosUpdating) {
    circular_buffer_write(&cb, 1);
    TEST_ASSERT_EQUAL(1, cb.writePos);
    circular_buffer_write(&cb, 1);
    TEST_ASSERT_EQUAL(2, cb.writePos);
}

TEST(CircularBuffer, ReadPosUpdating) {
    circular_buffer_write(&cb, 1);
    circular_buffer_write(&cb, 1);

    circular_buffer_read(&cb);
    TEST_ASSERT_EQUAL(1, cb.readPos);
    circular_buffer_read(&cb);
    TEST_ASSERT_EQUAL(2, cb.readPos);
}

TEST(CircularBuffer, Write158) {
    circular_buffer_write(&cb, 1);
    circular_buffer_write(&cb, 5);
    circular_buffer_write(&cb, 8);
    TEST_ASSERT_EQUAL(1, cb.p_buffer[0]);
    TEST_ASSERT_EQUAL(5, cb.p_buffer[1]);
    TEST_ASSERT_EQUAL(8, cb.p_buffer[2]);
}

TEST(CircularBuffer, Read269) {
    circular_buffer_write(&cb, 2);
    circular_buffer_write(&cb, 6);
    circular_buffer_write(&cb, 9);
    TEST_ASSERT_EQUAL(2, circular_buffer_read(&cb));
    TEST_ASSERT_EQUAL(6, circular_buffer_read(&cb));
    TEST_ASSERT_EQUAL(9, circular_buffer_read(&cb));
}

static void fillBufferWithOnes(void) {
    for(uint8_t i=0; i<cb.size; i++) {
        circular_buffer_write(&cb, 1);
    }
}

TEST(CircularBuffer, WritePosOverflow) {
    fillBufferWithOnes();
    TEST_ASSERT_EQUAL(0, cb.writePos);
    fillBufferWithOnes();
    TEST_ASSERT_EQUAL(0, cb.writePos);
    fillBufferWithOnes();
    TEST_ASSERT_EQUAL(0, cb.writePos);
}

TEST(CircularBuffer, ReadPosOverflow) {
    fillBufferWithOnes();
    TEST_ASSERT_EQUAL(0, cb.readPos);
    circular_buffer_read(&cb);
    TEST_ASSERT_EQUAL(1, cb.readPos);
    circular_buffer_read(&cb);
    TEST_ASSERT_EQUAL(2, cb.readPos);
    circular_buffer_read(&cb);
    TEST_ASSERT_EQUAL(0, cb.readPos);
}

TEST(CircularBuffer, Length) {
    TEST_ASSERT_EQUAL(0, circular_buffer_length(&cb));
    circular_buffer_write(&cb, 1);
    TEST_ASSERT_EQUAL(1, circular_buffer_length(&cb));
    circular_buffer_write(&cb, 1);
    TEST_ASSERT_EQUAL(2, circular_buffer_length(&cb));
    
    circular_buffer_read(&cb);
    TEST_ASSERT_EQUAL(1, circular_buffer_length(&cb));
    circular_buffer_read(&cb);
    TEST_ASSERT_EQUAL(0, circular_buffer_length(&cb));

    circular_buffer_write(&cb, 1);
    TEST_ASSERT_EQUAL(1, circular_buffer_length(&cb));
}

TEST(CircularBuffer, ReadWhenEmpty) {
    for(uint8_t i=0; i<cb.size; i++) {
        cb.p_buffer[i] = i+1;
    }
    TEST_ASSERT_EQUAL(0, circular_buffer_read(&cb));
}

TEST(CircularBuffer, WriteWhenFull) {
    fillBufferWithOnes();
    circular_buffer_write(&cb, 2);
    circular_buffer_write(&cb, 3);
    circular_buffer_write(&cb, 4);
    circular_buffer_write(&cb, 5);
    circular_buffer_write(&cb, 6);
    circular_buffer_write(&cb, 7);
    for(uint8_t i=0; i<cb.size; i++) {
        TEST_ASSERT_EQUAL(1, cb.p_buffer[i]);
    }
}

TEST_GROUP_RUNNER(CircularBuffer) {
    RUN_TEST_CASE(CircularBuffer, Initialize);
    RUN_TEST_CASE(CircularBuffer, WriteOne);
    RUN_TEST_CASE(CircularBuffer, ReadOne);
    RUN_TEST_CASE(CircularBuffer, WritePosUpdating);
    RUN_TEST_CASE(CircularBuffer, ReadPosUpdating);
    RUN_TEST_CASE(CircularBuffer, Write158);
    RUN_TEST_CASE(CircularBuffer, Read269);
    RUN_TEST_CASE(CircularBuffer, WritePosOverflow);
    RUN_TEST_CASE(CircularBuffer, ReadPosOverflow);
    RUN_TEST_CASE(CircularBuffer, Length);
    RUN_TEST_CASE(CircularBuffer, ReadWhenEmpty);
    RUN_TEST_CASE(CircularBuffer, WriteWhenFull);
}
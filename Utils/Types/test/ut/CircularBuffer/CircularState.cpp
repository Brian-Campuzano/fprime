/**
 * FakeLogger.cpp:
 *
 * Setup a fake logger for use with the testing. This allows for the capture of messages from the system and ensure that
 * the proper log messages are coming through as expected.
 *
 * @author mstarch
 */
#include <STest/Pick/Pick.hpp>
#include <Utils/Types/test/ut/CircularBuffer/CircularState.hpp>

#include <cstdlib>
#include <cstring>
#include <gtest/gtest.h>

U8 CIRCULAR_BUFFER_MEMORY[MAX_BUFFER_SIZE];
namespace MockTypes {

    CircularState::CircularState() :
        m_remaining_size(static_cast<FwSizeType>(sizeof(CIRCULAR_BUFFER_MEMORY))),
        m_random_size(MAX_BUFFER_SIZE),
        m_peek_offset(0),
        m_peek_type(0),
        m_infinite_store(nullptr),
        m_infinite_read(0),
        m_infinite_write(0),
        m_infinite_size(0),
        m_test_buffer(CIRCULAR_BUFFER_MEMORY, static_cast<FwSizeType>(sizeof(CIRCULAR_BUFFER_MEMORY)))
    {
        memset(m_buffer, 0, sizeof m_buffer);
    }

    CircularState::~CircularState() {
        if (m_infinite_size != 0) {
            std::free(m_infinite_store);
        }
    }

    // Generates a random buffer
    FwSizeType CircularState::generateRandomBuffer() {
        m_peek_offset = static_cast<FwSizeType>(STest::Pick::lowerUpper(0, sizeof(m_buffer)));
        m_peek_type = static_cast<FwSizeType>(STest::Pick::lowerUpper(0, 4));
        FwSizeType random_size = static_cast<FwSizeType>(STest::Pick::lowerUpper(0, sizeof(m_buffer)));
        for (U32 i = 0; i < random_size; i++) {
            m_buffer[i] = static_cast<U8>(STest::Pick::lowerUpper(0, 256));
        }
        this->m_random_size = random_size;
        return random_size;
    }

    void CircularState::setRandom(FwSizeType random, FwSizeType peek_type, FwSizeType peek_offset) {
        m_random_size = random;
        m_peek_type = peek_type;
        m_peek_offset = peek_offset;
    }

    FwSizeType CircularState::getPeekOffset() const {
        return m_peek_offset;
    }

    FwSizeType CircularState::getPeekType() const {
        return m_peek_type;
    }

    bool CircularState::addInfinite(const U8* buffer, FwSizeType size) {
        // If we are out of "infinite space" add another MB, and check allocation
        if ((m_infinite_write + size) > m_infinite_size) {
            void* new_pointer = std::realloc(m_infinite_store, m_infinite_size + 1048576);
            if (new_pointer == nullptr) {
                return false;
            }
            m_infinite_store = static_cast<U8*>(new_pointer);
            m_infinite_size += 1048576;
        }
        std::memcpy(m_infinite_store + m_infinite_write, buffer, size);
        m_infinite_write += size;
        return true;
    }

    bool CircularState::peek(U8*& buffer, FwSizeType size, FwSizeType offset) {
        FwSizeType final_offset = m_infinite_read + offset;
        if ((final_offset + size) > m_infinite_write) {
            return false;
        }
        buffer = m_infinite_store + final_offset;
        return true;
    }

    bool CircularState::rotate(FwSizeType size) {
        // Fail if we try to rotate too far
        if ((m_infinite_read + size) > m_infinite_write) {
            return false;
        }
        m_infinite_read += size;
        return true;
    }

    FwSizeType CircularState::getRandomSize() const {
        return m_random_size;
    }

    const U8 *CircularState::getBuffer() const {
        return m_buffer;
    }

    FwSizeType CircularState::getRemainingSize() const {
        return m_remaining_size;
    }

    void CircularState::setRemainingSize(FwSizeType mRemainingSize) {
        m_remaining_size = mRemainingSize;
    }

    Types::CircularBuffer& CircularState::getTestBuffer() {
        return m_test_buffer;
    }

    void CircularState::checkSizes() const {
        const FwSizeType allocated_size = (MAX_BUFFER_SIZE - m_remaining_size);
        ASSERT_EQ(m_test_buffer.get_free_size(), m_remaining_size);
        ASSERT_EQ(m_test_buffer.get_allocated_size(), allocated_size);
    }
}

#ifndef SERVER_PAYLOAD_HPP
#define SERVER_PAYLOAD_HPP

#include <cstddef>
#include <array>

struct ServerPayload {
    static constexpr size_t size = 12;

    using Buffer = std::array<uint8_t, size>;

    uint32_t id;
    uint32_t x;
    uint32_t y;

    Buffer encode() const {
        Buffer buffer;
        buffer[0]  = id >> 24;
        buffer[1]  = id >> 16;
        buffer[2]  = id >> 8;
        buffer[3]  = id;
        
        buffer[4]  = x >> 24;
        buffer[5]  = x >> 16;
        buffer[6]  = x >> 8;
        buffer[7]  = x;

        buffer[8]  = y >> 24;
        buffer[9]  = y >> 16;
        buffer[10] = y >> 8;
        buffer[11] = y;
        return buffer;
    }

    void decode(Buffer& buffer) {
        id = buffer[0] << 24;
        id |= buffer[1] << 16;
        id |= buffer[2] << 8;
        id |= buffer[3];

        x = buffer[4] << 24;
        x |= buffer[5] << 16;
        x |= buffer[6] << 8;
        x |= buffer[7];
    
        y = buffer[8] << 24;
        y |= buffer[9] << 16;
        y |= buffer[10] << 8;
        y |= buffer[11];
    }
};

#endif
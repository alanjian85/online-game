#ifndef CLIENT_PAYLOAD_HPP
#define CLIENT_PAYLOAD_HPP

#include <cstdint>
#include <array>

struct ClientPayload {
    using Buffer = std::array<uint8_t, 5>;

    uint32_t id;
    bool forward;
    bool backward;
    bool left;
    bool right;

    Buffer encode() const {
        Buffer buffer;
        buffer[0] = id >> 24;
        buffer[1] = id >> 16;
        buffer[2] = id >> 8;
        buffer[3] = id;
        buffer[4] = (forward << 3) | (backward << 2) | (left << 1) | right;
        return buffer;
    }

    void decode(Buffer& buffer) {
        id = buffer[0] << 24;
        id |= buffer[1] << 16;
        id |= buffer[2] << 8;
        id |= buffer[3];
        forward  = (buffer[4] >> 3) & 0x1;
        backward = (buffer[4] >> 2) & 0x1;
        left     = (buffer[4] >> 1) & 0x1;
        right    = buffer[4] & 0x1;
    }
};

#endif
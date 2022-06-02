#include "PlayerState.hpp"

#include <cassert>

std::vector<uint8_t> PlayerState::serialize() {
    std::vector<uint8_t> buffer;
    buffer.reserve(5);
    buffer.push_back((id >> 24) & 0xFF);
    buffer.push_back((id >> 16) & 0xFF);
    buffer.push_back((id >>  8) & 0xFF);
    buffer.push_back((id >>  0) & 0xFF);
    buffer.push_back(
        (forward  << 3) | 
        (backward << 2) | 
        (left     << 1) | 
        (right    << 0)
    );
    return buffer;
}

void PlayerState::deserialize(const std::vector<uint8_t>& buffer) {
    assert(buffer.size() == 5);
    id  = buffer[0] << 24;
    id |= buffer[1] << 16;
    id |= buffer[2] << 8;
    id |= buffer[3];
    forward  = buffer[4] & (1 << 3);
    backward = buffer[4] & (1 << 2);
    left     = buffer[4] & (1 << 1);
    right    = buffer[4] & (1 << 0);
}
#include "PlayerState.hpp"

#include <cassert>

std::vector<uint8_t> PlayerState::serialize() {
    std::vector<uint8_t> data;
    data.reserve(5);
    data.push_back((id >> 24) & 0xFF);
    data.push_back((id >> 16) & 0xFF);
    data.push_back((id >>  8) & 0xFF);
    data.push_back((id >>  0) & 0xFF);
    data.push_back(
        (forward  << 3) | 
        (backward << 2) | 
        (left     << 1) | 
        (right    << 0)
    );
    return data;
}

void PlayerState::deserialize(const std::vector<uint8_t>& data) {
    assert(data.size() == 5);
    id  = data[0] << 24;
    id |= data[1] << 16;
    id |= data[2] << 8;
    id |= data[3];
    forward  = data[5] & (1 << 3);
    backward = data[5] & (1 << 2);
    left     = data[5] & (1 << 1);
    right    = data[5] & (1 << 0);
}
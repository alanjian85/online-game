#include "PlayerState.hpp"

std::array<uint8_t, PLAYER_PACKET_SIZE> PlayerState::serialize() {
    std::array<uint8_t, PLAYER_PACKET_SIZE> buffer;
    buffer[0] = (id >> 24) & 0xFF;
    buffer[1] = (id >> 16) & 0xFF;
    buffer[2] = (id >>  8) & 0xFF;
    buffer[3] = (id >>  0) & 0xFF;
    buffer[4] = (forward  << 3) | 
                (backward << 2) | 
                (left     << 1) | 
                (right    << 0);
    return buffer;
}

void PlayerState::deserialize(const std::array<uint8_t, PLAYER_PACKET_SIZE>& buffer) {
    id  = buffer[0] << 24;
    id |= buffer[1] << 16;
    id |= buffer[2] << 8;
    id |= buffer[3];
    forward  = buffer[4] & (1 << 3);
    backward = buffer[4] & (1 << 2);
    left     = buffer[4] & (1 << 1);
    right    = buffer[4] & (1 << 0);
}
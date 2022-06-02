#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <cstdint>
#include <array>

#include "constants.hpp"

struct PlayerState {
    int x;
    int y;

    uint32_t id;
    bool forward;
    bool backward;
    bool left;
    bool right;

    std::array<uint8_t, PLAYER_PACKET_SIZE> serialize();

    void deserialize(const std::array<uint8_t, PLAYER_PACKET_SIZE>& buffer);
};

#endif
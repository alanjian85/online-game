#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <cstdint>
#include <vector>

struct PlayerState {
    uint32_t id;
    bool forward;
    bool backward;
    bool left;
    bool right;

    std::vector<uint8_t> encode();

    void decode(const std::vector<uint8_t>& data);
};

#endif
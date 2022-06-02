#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <cstdint>
#include <array>
#include <mutex>

#include "constants.hpp"

class PlayerState {
public:
    PlayerState();

    std::array<uint8_t, PLAYER_PACKET_SIZE> serialize() const;

    void deserialize(const std::array<uint8_t, PLAYER_PACKET_SIZE>& buffer);

    void setForward(bool forward);

    void setBackward(bool backward);

    void setLeft(bool left);

    void setRight(bool right);

    int getX() const;

    int getY() const;
private:
    mutable std::mutex m_mutex;
    int m_x;
    int m_y;

    uint32_t m_id;
    bool m_forward;
    bool m_backward;
    bool m_left;
    bool m_right;
};

#endif
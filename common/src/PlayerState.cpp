#include "PlayerState.hpp"

#include "constants.hpp"

PlayerState::PlayerState() {
    m_x = PLAYER_SPAWN_X;
    m_y = PLAYER_SPAWN_Y;
    m_id = UINT32_MAX;
}

std::array<uint8_t, PLAYER_PACKET_SIZE> PlayerState::serialize() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::array<uint8_t, PLAYER_PACKET_SIZE> buffer;
    buffer[0] = (m_id >> 24) & 0xFF;
    buffer[1] = (m_id >> 16) & 0xFF;
    buffer[2] = (m_id >>  8) & 0xFF;
    buffer[3] = (m_id >>  0) & 0xFF;
    buffer[4] = (m_forward  << 3) | 
                (m_backward << 2) | 
                (m_left     << 1) | 
                (m_right    << 0);
    return buffer;
}

void PlayerState::deserialize(const std::array<uint8_t, PLAYER_PACKET_SIZE>& buffer) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_id  = buffer[0] << 24;
    m_id |= buffer[1] << 16;
    m_id |= buffer[2] << 8;
    m_id |= buffer[3];
    m_forward  = buffer[4] & (1 << 3);
    m_backward = buffer[4] & (1 << 2);
    m_left     = buffer[4] & (1 << 1);
    m_right    = buffer[4] & (1 << 0);
}

void PlayerState::setForward(bool forward) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_forward = forward;
}

void PlayerState::setBackward(bool backward) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_backward = backward;
}

void PlayerState::setLeft(bool left) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_left = left;
}

void PlayerState::setRight(bool right) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_right = right;
}

int PlayerState::getX() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_x;
}

int PlayerState::getY() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_y;
}
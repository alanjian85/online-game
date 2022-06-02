#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <mutex>

class Player {
public:
    void setPosition(int x, int y) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_x = x;
        m_y = y;
    }

    void getPosition(int& x, int& y) const {
        std::lock_guard<std::mutex> lock(m_mutex);
        x = m_x;
        y = m_y;
    }

private:
    mutable std::mutex m_mutex;
    int m_x;
    int m_y;
};

#endif
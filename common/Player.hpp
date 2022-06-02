#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
public:
    void setPosition(int x, int y);

    void getPosition(int& x, int& y) const;
};

#endif
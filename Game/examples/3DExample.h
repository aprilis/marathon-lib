#ifndef THREEDEXAMPLE_H
#define THREEDEXAMPLE_H

#include "../lib/Game.h"

class ThreeDExample : public Game
{
    static const int N = 10;
    sf::Color map[N][N][N];

protected:
    void sync();

public:
    ThreeDExample(int width, int height);
};

#endif // THREEDEXAMPLE_H


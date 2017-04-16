#ifndef TEST_H
#define TEST_H

//Przyklad komunikacji z gra (z PIZZY)

#include "../lib/Game.h"
using namespace std;

class Maze : public Game
{
protected:
    void draw();

    void myProcessEvent(const sf::Event &event);

    void sync();

    void sendCommands();

    pair<int, int> move;

    int mx = 0, my = 0;

public:
    Maze(int width, int height);
};

#endif // TEST_H

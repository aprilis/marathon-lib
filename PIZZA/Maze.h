#ifndef TEST_H
#define TEST_H

#include "Game.h"
using namespace std;

//to jest najwazniejsza klasa w programie
class Maze : public Game
{
protected:
    //tu deklarujemy funkcje z klasy Game ktore chcemy zmienic
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

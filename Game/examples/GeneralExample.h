#ifndef GENERALEXAMPLE_H
#define GENERALEXAMPLE_H

//Przyklad pokazujacy uzycie wielu podstawowych funkcji (tworzenie i rysowanie ksztaltow, uzycie info itd)

#include "../lib/Game.h"

class GeneralExample : public Game
{
protected:
    void myProcessEvent(const sf::Event &event);

    void sync();

    bool show_turns = false;

    string text;

public:
    GeneralExample(int width, int height);
};

#endif // GENERALEXAMPLE_H

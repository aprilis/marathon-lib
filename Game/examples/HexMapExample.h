#ifndef HEXMAP_EXAMPLE_H
#define HEXMAP_EXAMPLE_H

//Przyklad pokazujacy wykorzystanie hex mapy

#include "../lib/Game.h"
#include "../lib/HexMap.h"

class HexMapExample : public Game
{
    void leftClick(sf::Vector2f position);

    void sync();

    HexMap map;

    int redItems = 0;

public:
    HexMapExample(int width = 0, int height = 0);
};

#endif // HEXMAP_EXAMPLE_H


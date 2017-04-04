#ifndef HEXMAP_H
#define HEXMAP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace std;

class HexMap
{
    vector<vector<sf::CircleShape>> hexes;

    float radius = 1.f;

    const float h_factor = 0.9, v_factor = 0.8;

public:
    HexMap() = default;

    HexMap(int rows, int columns, float size = 30.f) { init(rows, columns, size); }

    void init(int rows, int columns, float size = 30.f);

    void setColor(int row, int column, sf::Color color);

    sf::Vector2f getPosition(int row, int column) const;

    //returns pair (row, column) or (-1, -1) if position is outside map
    pair<int, int> getHex(sf::Vector2f position) const;

    void draw(Game &game) const;

    void draw(sf::RenderWindow &window) const;
};

#endif // HEXMAP_H


#include "HexMap.h"
#include <iostream>

void HexMap::init(int rows, int columns, float size)
{
    radius = size / 2;
    hexes.clear();
    hexes.resize(rows, vector<sf::CircleShape>(columns, sf::CircleShape(radius, 6)));
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
        {
            hexes[i][j].setPosition(radius * (j * 2 + i % 2) * h_factor, radius * (i * 2 + 1) * v_factor);
            hexes[i][j].setFillColor(sf::Color::White);
            hexes[i][j].setOrigin(radius, radius);
        }
}

void HexMap::setColor(int row, int column, sf::Color color)
{
    if(row >= 0 && row < hexes.size() && column >= 0 && column < hexes[0].size())
        hexes[row][column].setFillColor(color);
    else cerr << "WARNING: index out of range" << endl;
}

sf::Vector2f HexMap::getPosition(int row, int column) const
{
    if(row >= 0 && row < hexes.size() && column >= 0 && column < hexes[0].size())
        return hexes[row][column].getPosition();
    else cerr << "WARNING: index out of range" << endl;
    return sf::Vector2f();
}

pair<int, int> HexMap::getHex(sf::Vector2f position) const
{
    if(hexes.empty()) return make_pair(-1, -1);
    int column = floor(position.x / (radius * 2 * h_factor)), row = floor(position.y / (radius * 2 * v_factor));
    pair<int, int> best(-1, -1);
    float min_dist = radius * radius;
    int rows = hexes.size(), columns = hexes[0].size();
    for(int i = max(0, row - 2); i < min(rows, row + 3); i++)
        for(int j = max(0, column - 2); j < min(columns, column + 3); j++)
        {
            auto offset = position - hexes[i][j].getPosition();
            auto dist = offset.x * offset.x + offset.y * offset.y;
            if(dist < min_dist)
            {
                min_dist = dist;
                best = make_pair(i, j);
            }
        }
    return best;
}

void HexMap::draw(Game &game) const
{
    for(const auto &x: hexes)
        for(const auto &y: x)
            game.addDrawable(y);
}

void HexMap::draw(sf::RenderWindow &window) const
{
    for(const auto &x: hexes)
        for(const auto &y: x)
            window.draw(y);
}

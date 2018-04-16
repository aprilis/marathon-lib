#include "HexMap.h"
#include "Common.h"
#include <iostream>

void HexMap::init(int rows, int columns, float size)
{
    radius = size / 2;
    hexes.clear();
    hexes.resize(rows, vector<sf::CircleShape>(columns));
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
        {
            hexes[i][j] = makeCircle(radius, radius * (j * 2 + i % 2) * h_factor, radius * (i * 2 + 1) * v_factor, sf::Color::White);
            hexes[i][j].setPointCount(6);
        }
}

void HexMap::setColor(int row, int column, sf::Color color)
{
    if(row >= 0 && row < rowCount() && column >= 0 && column < colCount())
        hexes[row][column].setFillColor(color);
    else cerr << "WARNING: index out of range" << endl;
}

sf::Color HexMap::getColor(int row, int column) const
{
    if(row >= 0 && row < rowCount() && column >= 0 && column < colCount())
        return hexes[row][column].getFillColor();
    else
    {
        cerr << "WARNING: index out of range" << endl;
        return sf::Color();
    }
}

sf::Vector2f HexMap::getPosition(int row, int column) const
{
    if(row >= 0 && row < rowCount() && column >= 0 && column < colCount())
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
    int rows = rowCount(), columns = colCount();
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

void HexMap::draw(GameState &gameState) const
{
    for(const auto &x: hexes)
        for(const auto &y: x)
            gameState.addDrawable(y);
}

void HexMap::draw(sf::RenderWindow &window) const
{
    for(const auto &x: hexes)
        for(const auto &y: x)
            window.draw(y);
}

static int move_x[2][6] = {{0, 0, 1, -1, 1, -1}, {0, 0, 1, -1, -1, 1}};
static int move_y[2][6] = {{1, -1, 0, 0, -1, -1}, {1, -1, 0, 0, 1, 1}};

vector<pair<int, int>> HexMap::getNeighbours(int row, int column) const
{
    vector<pair<int, int>> result;
    for(int i = 0; i < 6; i++)
    {
        auto res = make_pair(row + move_x[row % 2][i], column + move_y[row % 2][i]);
        if(res.first >= 0 && res.second >= 0 && res.first < rowCount() && res.second < colCount())
            result.push_back(res);
    }
    return result;
}


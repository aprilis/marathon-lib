#include "HexMapExample.h"

HexMapExample::HexMapExample(int width, int height) : Game(width, height, "Hex Map Example")
{
    map.init(10, 30, 50); //rows, columns, hex size
    info.addItem("red fields", redItems);
}

void HexMapExample::sync()
{
    map.draw(gameState);
}

void HexMapExample::leftClick(sf::Vector2f position)
{
    auto p = map.getHex(position);
    if(p.first != -1)
    {
        auto nei =  map.getNeighbours(p.first, p.second);
        for(auto n: nei)
            map.setColor(n.first, n.second, sf::Color::Red);
        map.setColor(p.first, p.second, sf::Color::Green);

        //update redItems
        redItems = 0;
        for(int i = 0; i < map.rowCount(); i++)
            for(int j = 0; j < map.colCount(); j++)
                if(map.getColor(i, j) == sf::Color::Red)
                    redItems++;
    }
}

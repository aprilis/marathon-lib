#include "3DExample.h"
#include <iostream>
#include "../lib/Common.h"
#include <vector>
#include <cstdlib>

ThreeDExample::ThreeDExample(int width, int height) : Game(width, height, "Example")
{
    vector<sf::Color> colors = { sf::Color::Red, sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Cyan };
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            for(int k = 0; k < N; k++)
                if(rand() % 10 == 0)
                    map[i][j][k] = colors[rand() % colors.size()];
}

void ThreeDExample::sync()
{
    const float size = 20, gap = 5;
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            for(int k = 0; k < 10; k++)
                if(map[i][j][k] != sf::Color::Black)
                    addCube({ (size + gap) * i, (size + gap) * j, (size + gap) * k }, map[i][j][k], size);
}

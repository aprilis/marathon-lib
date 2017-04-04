#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "StreamWindow.h"
#include "Config.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Info.h"
using namespace std;

class GameState
{
    string current_out;
    string current_err;

    StreamWindow *window;

    vector<pair<unique_ptr<sf::Drawable>, sf::Transform>> drawables;

    sf::Transform readTransform();
    void readShape(sf::Shape &shape);
    sf::Drawable* readRect();
    sf::Drawable* readCircle();
    sf::Drawable* readConvex();
    sf::Drawable* readText();

    int readLine();

    vector<streampos> turns;

    ifstream in;

    Info &inf;

public:
    GameState(string path, Info &info);

    ~GameState();

    void update();

    bool nextTurn();
    bool prevTurn();

    void draw(sf::RenderWindow &win);
};

#endif // GAMESTATE_H


#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "StreamWindow.h"
#include "Log.h"
#include "Config.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
using namespace std;

class GameState
{
    static stringstream out_stream;
    static stringstream err_stream;

    string current_out;
    string current_err;

    StreamWindow *window;

    vector<unique_ptr<sf::Drawable>> drawables;

    void logStream(const string &name, const string &str);

    void logTransform(const sf::Transform &transform);
    void logShape(const sf::Shape &shape);
    void logObject(const sf::RectangleShape &obj);
    void logObject(const sf::CircleShape &obj);
    void logObject(const sf::ConvexShape &obj);
    void logObject(const sf::Text &obj);

public:
    static ofstream log;

    GameState(string title = "Output");

    ~GameState();

    void showWindow();

    void nextTurn();

    void update();

    void clearDrawables() { drawables.clear(); }

    template<class T> void addDrawable(const T &x)
    {
        drawables.emplace_back(new T(x));
#ifdef SAVE_GAME
        logObject(x);
        log << "\n";
#endif
    }

    void draw(sf::RenderWindow &win);
};

#endif // GAMESTATE_H


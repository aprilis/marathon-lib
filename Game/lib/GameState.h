#ifndef GAMESTATE_H
#define GAMESTATE_H

/*!
 * \file
 * \brief Contains the GameState class
 */

#include "StreamWindow.h"
#include "Log.h"
#include "Config.h"
#include "Transform.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
using namespace std;

//! This class contains the state of the game. It draws it, shows the output window and saves game for further viewing
class GameState
{
    struct Cube
    {
        sf::Vector3f position;
        sf::Color color;
        sf::Vector3f size;
    };

    static stringstream out_stream;
    static stringstream err_stream;

    string current_out;
    string current_err;

    StreamWindow *window;

    vector<unique_ptr<sf::Drawable>> drawables;
    vector<Cube> cubes;
    sf::Vector3f faceShift[6];

    void logStream(const string &name, const string &str);

    void logTransform(const sf::Transform &transform);
    void logShape(const sf::Shape &shape);
    void logObject(const sf::RectangleShape &obj);
    void logObject(const sf::CircleShape &obj);
    void logObject(const sf::ConvexShape &obj);
    void logObject(const sf::Text &obj);

    void logCube(Cube cube);

public:
    static ofstream log;

    /*!
     * \brief GameState
     * \param title The output window's title
     */
    GameState(string title = "Output");

    ~GameState();

    /*!
     * \brief Shows the window with the content of mout and merr
     */
    void showWindow();

    void nextTurn();

    void update();

    void clearDrawables() { drawables.clear(); cubes.clear(); }

    /*!
     * \brief Adds x to the drawables list
     *
     * The drawable can be one of the following types: sf::CircleShape, sf::RectangleShape, sf::ConvexShape, sf::Text.
     * It is shown until the next turn and saved for later replays.
     * Every object should be added only once per turn.
     */
    template<class T> void addDrawable(const T &x)
    {
        drawables.emplace_back(new T(x));
#ifdef SAVE_GAME
        logObject(x);
        log << "\n";
#endif
    }

    void addCube(sf::Vector3f position, sf::Color color, sf::Vector3f size);
    void addCube(sf::Vector3f position, sf::Color color, float size);

    void draw(sf::RenderWindow &win);
    void draw3D(sf::RenderWindow &win, Transform transform);
};

#endif // GAMESTATE_H


#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Info.h"
#include "Config.h"
#include "GameState.h"
#include <thread>
#include <mutex>
#include <sstream>
using namespace std;

//od tej klasy trzeba zrobic klase pochodna (dziedziczaca)
class Game
{
protected:
    const float timeStep = 1.f / FPS;

    sf::RenderWindow window;

    sf::View view;

    sf::Vector2f mouseClick;

    sf::Clock mouseClickTime;

    sf::Clock turnTime;

    bool mousePressed = false;

    Info info;

    bool end = false;

    float turnDuration = TURN_DURATION;

    void processEvent(const sf::Event &event);

    void updateCamera();

    int turnsLeft = 1e9;

    GameState gameState;

    void drawSelection();

    //funkcje poprzedzone slowkiem virtual mozna podmienic w dziedziczacej klasie
    virtual void draw() { }

    virtual void update() { }

    virtual void sync() { }

    virtual void firstSync() { sync(); }

    virtual void sendCommands() { }

    virtual void myProcessEvent(const sf::Event &event) { }

    virtual void leftClick(sf::Vector2f position) { }

    virtual void rightClick(sf::Vector2f position) { }

    virtual void selectedRect(sf::FloatRect rect) { }

    void runSync();

    void nextTurn();

    float timeLeft() const { return max(0.f, turnDuration - turnTime.getElapsedTime().asSeconds()); }

    mutex mut;

    bool playing = false;

public:
    Game(int windowWidth, int windowHeight, string title = "PIZZA");

    sf::Vector2f getMousePosition();

    void moveCamera(float cx, float cy, float zoom = 1.f);

    void run();

    template<class T> void addDrawable(const T &x) { gameState.addDrawable(x); }

    void showOutputWindow() { gameState.showWindow(); }
};

#endif // GAME_H

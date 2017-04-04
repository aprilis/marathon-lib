#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Info.h"
#include "Config.h"
#include "GameState.h"
#include <sstream>
using namespace std;

//od tej klasy trzeba zrobic klase pochodna (dziedziczaca)
class Game
{
protected:
    const float timeStep = 1.f / FPS;

    sf::RenderWindow window;

    sf::View view;

    sf::Clock turnTime;

    Info info;

    bool end = false;

    float turnDuration = TURN_DURATION;

    int speed = 1;

    void processEvent(const sf::Event &event);

    void updateCamera();

    GameState gameState;

    float timeLeft() const { return max(0.f, turnDuration - turnTime.getElapsedTime().asSeconds()); }

    bool playing = false;

    void nextTurn();
    void prevTurn();

public:
    Game(int windowWidth, int windowHeight, string path, string title = "PIZZA");

    sf::Vector2f getMousePosition();

    void moveCamera(float cx, float cy, float zoom = 1.f);

    void run();
};

#endif // GAME_H

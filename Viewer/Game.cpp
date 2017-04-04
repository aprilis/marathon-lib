#include "Game.h"
#include "Config.h"
#include <QApplication>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace std;

double length(sf::Vector2f vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

Game::Game(int windowWidth, int windowHeight, string path, string title)
    : window(sf::VideoMode(windowWidth, windowHeight), title), gameState(path, info)
{
}

sf::Vector2f Game::getMousePosition()
{
    auto pos = sf::Mouse::getPosition(window);
    return window.mapPixelToCoords(pos, view);
}

void Game::run()
{
    end = false;

#if defined AUTO_TURN_DURATION && defined TCP
    wait();
    sf::Clock durationClock;
    wait();
    turnDuration = max(0.1, durationClock.getElapsedTime().asSeconds() * TURN_DURATION_RATIO);
#endif

    nextTurn();

    float time = 0.f;
    sf::Clock clock;

    bool redraw = false;
    playing = true;

    while(window.isOpen())
    {
        time += clock.restart().asSeconds();
        if(time < timeStep)
            usleep((timeStep - time) * 1000000);

        sf::Event event;
        while(window.pollEvent(event))
            processEvent(event);

        while(time > timeStep)
        {
            updateCamera();
            redraw = true;
            time -= timeStep;
        }
        if(end == true) break;
        if(redraw)
        {
            window.clear();
            window.setView(view);
            gameState.draw(window);
            window.setView(window.getDefaultView());
            info.popItem();
            info.addItem("speed: " + to_string(speed));
            info.draw(window);
            window.display();
        }
        if(fabs(turnTime.getElapsedTime().asSeconds() * speed) > turnDuration)
        {
            turnTime.restart();
            if(speed < 0) prevTurn();
            else if(speed > 0) nextTurn();
        }
        QApplication::processEvents();
    }
    playing = false;
}

void Game::processEvent(const sf::Event &event)
{
    const int maxClickTime = 500;
    const float zoomFactor = 0.05f;
    const double maxClickMove = 3;

    if(event.type == sf::Event::Closed)
    {
        window.close();
        exit(0);
    }
    else if(event.type == sf::Event::MouseWheelMoved)
    {
        int delta = event.mouseWheel.delta;
        view.zoom(1 - zoomFactor * delta);
    }
    else if(event.type == sf::Event::KeyReleased)
    {
        switch(event.key.code)
        {
        case sf::Keyboard::Up:
            speed++;
            break;
        case sf::Keyboard::Down:
            speed--;
            break;
        case sf::Keyboard::Left:
            prevTurn();
            break;
        case sf::Keyboard::Right:
            nextTurn();
            break;
        }
    }
}

void Game::updateCamera()
{
    const int border = WINDOW_BORDER;
    const float speed = 300.f * view.getSize().x / window.getSize().x * timeStep;
    auto pos = sf::Mouse::getPosition(window);
    auto size = window.getSize();
    if(pos.x < 0 || pos.y < 0 || pos.x > size.x || pos.y > size.y) return;
    if(pos.x <= border) view.move(-speed, 0);
    if(pos.y <= border) view.move(0, -speed);
    if(pos.x >= (int)size.x - border) view.move(speed, 0);
    if(pos.y >= (int)size.y - border) view.move(0, speed);
}

void Game::moveCamera(float cx, float cy, float zoom)
{
    sf::Vector2f center(cx, cy);
    view.setCenter(center);
    view.setSize(window.getSize().x, window.getSize().y);
    view.zoom(zoom);
}

void Game::nextTurn()
{
    info.clear();
    if(!gameState.nextTurn()) speed = 0;
    info.addItem("");
    info.addItem("speed: " + to_string(speed));
}

void Game::prevTurn()
{
    info.clear();
    if(!gameState.prevTurn()) speed = 0;
    info.addItem("");
    info.addItem("speed: " + to_string(speed));
}

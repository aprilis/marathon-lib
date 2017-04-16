#include "Game.h"
#include "Wrapper.h"
#include "Config.h"
#include "Log.h"
#include <QApplication>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <unistd.h>
using namespace std;

double length(sf::Vector2f vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

Game::Game(int windowWidth, int windowHeight, string title)
    : window(sf::VideoMode(windowWidth, windowHeight), title), gameState(title)
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

    turnsLeft = ::turnsLeft();
    firstSync();
    nextTurn();

    float time = 0.f;
    sf::Clock clock;

    bool redraw = false;
    playing = true;
    thread syncThread(bind(&Game::runSync, this));

    while(window.isOpen())
    {
        time += clock.restart().asSeconds();
        if(time < timeStep)
            usleep((timeStep - time) * 1000000);

        sf::Event event;
        while(window.pollEvent(event))
        {
            mut.lock();
            processEvent(event);
            mut.unlock();
        }

        while(time > timeStep)
        {
            mut.lock();
            update();
            updateCamera();
            mut.unlock();
            redraw = true;
            time -= timeStep;
        }
        if(end == true) break;
        if(redraw)
        {
            mut.lock();
            window.clear();
            window.setView(view);
            gameState.draw(window);
            draw();
            drawSelection();
            window.setView(window.getDefaultView());
            info.draw(window);
            window.display();
            mut.unlock();
        }
        mut.lock();
        gameState.update();
        QApplication::processEvents();
        mut.unlock();
    }
    mut.lock();
    playing = false;
    mut.unlock();
    syncThread.join();
}

void Game::runSync()
{
    while(true)
    {
        try
        {
            {
                lock_guard<mutex> guard(mut);
                if(playing == false) break;
                try
                {
                    gameState.clearDrawables();
                    sync();
#ifndef SEND_COMMANDS_LATE
                    sendCommands();
#endif
#ifdef SAVE_GAME
                    info.log(gameState.log);
#endif
                }
                catch(pair<int, string> e)
                {
                    merr << "exception!: " << e.first << " " << e.second << "\n";
                    throw e;
                }
            }
#ifdef SEND_COMMANDS_LATE
            usleep(timeLeft() * 1000000);
            {
                lock_guard<mutex> guard(mut);
                try
                {
                    sendCommands();
                }
                catch(pair<int, string> e)
                {
                    merr << "exception!: " << e.first << " " << e.second << "\n";
                    throw e;
                }
            }
#else
            usleep(100);
#endif
            nextTurn();
            mout.flush();
            merr.flush();
        }
        catch(...)
        {
            end = true;
            break;
        }
    }
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
    else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        mousePressed = true;
        mouseClickTime.restart();
        mouseClick = getMousePosition();
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            mousePressed = false;
            auto m1 = mouseClick, m2 = getMousePosition();
#ifdef ENABLE_RECT_SELECTION
            if(mouseClickTime.getElapsedTime().asMilliseconds() > maxClickTime ||
                    length(m1 - m2) > maxClickMove)
            {
                float left = min(m1.x, m2.x), top = min(m1.y, m2.y), right = max(m1.x, m2.x), bottom = max(m1.y, m2.y);
                selectedRect(sf::FloatRect(left, top, right - left, bottom - top));
            }
            else
                leftClick(getMousePosition());
#else
            leftClick(getMousePosition());
#endif
        }
        else if(event.mouseButton.button == sf::Mouse::Right)
            rightClick(getMousePosition());
        else myProcessEvent(event);
    }
    else if(event.type == sf::Event::MouseWheelMoved)
    {
        int delta = event.mouseWheel.delta;
        view.zoom(1 - zoomFactor * delta);
    }
    else myProcessEvent(event);
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

void Game::drawSelection()
{
#ifdef ENABLE_RECT_SELECTION
    if(!mousePressed) return;
    sf::RectangleShape shape;
    auto m1 = mouseClick, m2 = getMousePosition();
    shape.setPosition(m1);
    shape.setSize(m2 - m1);
    shape.setFillColor(sf::Color(255, 255, 255, 100));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
    window.draw(shape);
#endif
}

void Game::nextTurn()
{
    mut.lock();
    gameState.nextTurn();
    mut.unlock();
#ifdef TURNS_LEFT_COMMAND
    int left = ::turnsLeft();
    if(left == turnsLeft)
    {
        wait();
        left = ::turnsLeft();
    }
    else if(left < turnsLeft)
    {
        merr << left << " " << turnsLeft << "\n";
        merr << "Przeskakujesz turę\n";
#ifdef TURN_MISSED_EXCEPTION
        throw make_pair(-5, "Turn missed");
#endif
    }
    if(left > turnsLeft)
    {
        merr << "Nowa gra\n";
        throw make_pair(-6, "Nowa gra");
    }
    turnTime.restart();
    turnsLeft = left;
#else
    wait();
    turnTime.restart();
#endif
#ifndef TCP
    sleep(1);
#endif
}

void Game::moveCamera(float cx, float cy, float zoom)
{
    sf::Vector2f center(cx, cy);
    view.setCenter(center);
    view.setSize(window.getSize().x, window.getSize().y);
    view.zoom(zoom);
}

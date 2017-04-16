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

/*!
 * \file
 * \brief Contains the main Game class
 */

//! The main Game class. You should make a derived class from it
class Game
{
protected:
    const float timeStep = 1.f / FPS;

    //! The window. You can use it to call window.draw(something)
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

    //! The turns left counter. It updates every turn
    int turnsLeft = 1e9;

    //! The game state. It contains all drawables and logs. Can be used to call gameState.addDrawable(something)
    GameState gameState;

    void drawSelection();

    //! You can override this function for custom real-time drawing
    virtual void draw() { }

    //! You can override this function for custom real-time updates
    virtual void update() { }

    //! This function should contain all synchronisation with server
    virtual void sync() { }

    //! You can override this function if you want the first sync to behave differently. Otherwise normal sync() will be called
    virtual void firstSync() { sync(); }

    /*! \brief You can write sending commands code in this function.
     *
     *  When SEND_COMMANDS_LATE if off it is run right after sync().
     *  Otherwise it is run after turnDuration which is either specified or measured automatically (not recommended)
     *
     *  CAUTION: this function is not run after firstSync() (you can do it manually)
     */
    virtual void sendCommands() { }

    /*!
     * \brief You can override this function for event handling. However, it doesn't handle mouse events
     * \param event the sfml event
     * \sa leftClick, rightClick, selectedRect
     */
    virtual void myProcessEvent(const sf::Event &event) { }

    /*!
     * \brief This function is called whenever the user clicks left mouse button
     * \param position the coordinates of mouse pointer after applying camera transform
     */
    virtual void leftClick(sf::Vector2f position) { }

    /*!
     * \brief This function is called whenever the user clicks right mouse button
     * \param position the coordinates of mouse pointer after applying camera transform
     */
    virtual void rightClick(sf::Vector2f position) { }

    /*!
     * \brief This function is called after selecting a rectangle area with mouse
     * \param rect the selected area
     */
    virtual void selectedRect(sf::FloatRect rect) { }

    void runSync();

    void nextTurn();

    float timeLeft() const { return max(0.f, turnDuration - turnTime.getElapsedTime().asSeconds()); }

    mutex mut;

    bool playing = false;

public:
    Game(int windowWidth, int windowHeight, string title = "Marathon");

    //! Returns mouse cursor position after applying camera transform
    sf::Vector2f getMousePosition();

    /*!
     * \brief Moves camera so that its centered at (cx, cy) and zoomed with specified factor
     * \param cx the x-coordinate of center
     * \param cy the y-coordinate of center
     * \param zoom the zoom factor
     */
    void moveCamera(float cx, float cy, float zoom = 1.f);

    /*!
     * \brief This function simply runs the game until the main window is closed or an exception fired
     */
    void run();

    //! This function simply calls gameState.addDrawable(x)
    template<class T> void addDrawable(const T &x) { gameState.addDrawable(x); }

    //! Shows window with content of mout and merr
    void showOutputWindow() { gameState.showWindow(); }

    //! Returns the number of turns left
    int getTurnsLeft() { return turnsLeft; }
};

#endif // GAME_H
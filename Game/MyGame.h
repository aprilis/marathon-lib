#ifndef MYGAME_H
#define MYGAME_H

#include "lib/Game.h"

//Szkielet gry
class MyGame : public Game
{
    void sync();

    void firstSync();

    void sendCommands();

    void myProcessEvent(const sf::Event &event);

    void leftClick(sf::Vector2f position);

    void myDraw(); //tutaj mozna dodawac wszystkie obiekty do rysowania (mozna tez w sync)

public:
    MyGame(int width, int height, string title = "MyGame");
};

#endif // MYGAME_H


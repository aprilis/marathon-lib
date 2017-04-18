#include "MyGame.h"
#include "lib/Common.h"

MyGame::MyGame(int width, int height, string title) : Game(width, height, title)
{
    info.addItem("turns left", turnsLeft);
}

void MyGame::sync()
{
    //tutaj synchronizacja

    myDraw();
}

void MyGame::firstSync()
{
    sync();
}

void MyGame::sendCommands()
{
    //tutaj mozna dodac kod wysylajacy komendy na serwer (ale mozna to tez zrobic w sync)
}

void MyGame::myDraw()
{
    //tutaj robimy rysowanie, na przyklad addDrawable(makeRectangle(50, 30, 100, 100, sf::Color::Red));
}

void MyGame::myProcessEvent(const sf::Event &event)
{
    if(event.type == sf::Event::KeyReleased)
    {
        auto key = event.key.code;
        //mozna teraz sprawdzic jaki klawisz zostal nacisniety na przyklad if(key == sf::Keyboard::W || key == sf::Keyboard::Up)
        if(key == sf::Keyboard::O)
            showOutputWindow();
    }
}

void MyGame::leftClick(sf::Vector2f position)
{
    //obsluga klikniecia myszka, na przyklad merr << position.x << " " << position.y << "\n";
}

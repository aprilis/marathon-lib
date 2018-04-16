#include "GeneralExample.h"
#include <iostream>
#include "../lib/Common.h"

//przykladowa funkcja zwracajaca stringa
string randomLetter()
{
    string s;
    s += (char)(rand() % ('z' - 'a' + 1) + 'a');
    return s;
}

GeneralExample::GeneralExample(int width, int height) : Game(width, height, "Example")
{
    //dodawanie informacji ktore sa wyswietlane na ekranie
    //mozna dac albo referencje do zmiennej albo funkcje zwracajaca stringa
    //info.addItem("etykieta", referencja_do_zmiennej);
    //info.addItem("etykieta2", funkcja_zwracajaca_stringa
    info.addFunction("random letter", randomLetter);
    info.addItem("text", text);
}

void GeneralExample::myProcessEvent(const sf::Event &event)
{
    if(event.type == sf::Event::KeyReleased)
        if(event.key.code == sf::Keyboard::Tab)
        {
            show_turns = !show_turns;
            if(show_turns) info.addItem("turns left", turnsLeft);
            else info.removeItem("turns left");
        }
    if(event.type == sf::Event::TextEntered)
        text += (char)event.text.unicode;
}

void GeneralExample::sync()
{
    //rysowanie prostokata na ekranie
    sf::RectangleShape shape = makeRectangle(50, 50, 500, 300, sf::Color::White);
    shape.rotate(75);
    addDrawable(shape);

    //dalej mozna uzyc tego samego obiektu shape do rysowania kolejnego prostokata)
    shape.setPosition(500, 100);
    shape.setFillColor(sf::Color(120, 120, 0));
    addDrawable(shape);

    shape = makeRectangle(100, 100, 600, 100, sf::Color::Blue);
    addDrawable(shape);

    //a tutaj tworzymy linie
    shape = makeLine(600, 100, 500, 150, 10, sf::Color::Green);
    addDrawable(shape);

    //a tu kolko
    sf::CircleShape circle = makeCircle(30, 100, 100, sf::Color::Yellow);
    addDrawable(circle);

    sf::Text text = makeText("przykladowy tekst", 15, 600, 130, sf::Color::White);
    addDrawable(text);
}

void GeneralExample::consoleCommand(string command)
{
    console.stdout << "you typed " << command << endl;
}

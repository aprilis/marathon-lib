#include "Test.h"
#include "Settings.h"
#include <iostream>
#include "wrapper.h"

//przykladowa funkcja zwracajaca stringa
string randomLetter()
{
    string s;
    s += (char)(rand() % ('z' - 'a' + 1) + 'a');
    return s;
}

Test::Test(int width, int height) : Game(width, height)
{
    //dodawanie informacji ktore sa wyswietlane na ekranie
    //mozna dac albo referencje do zmiennej albo funkcje zwracajaca stringa
    //info.addItem("etykieta", referencja_do_zmiennej);
    //info.addItem("etykieta2", funkcja_zwracajaca_stringa
    info.addFunction("random letter", randomLetter);
    info.addItem("s", object.s);
    info.addItem("a", object.a);
    info.addItem("k", object.k);
    info.addFunction("x", [this]() { return object.x ? "true" : "false"; });
    info.addItem("text", text);

    hex.init(20, 20, 20.f);
}

void Test::draw()
{
}

void Test::myProcessEvent(const sf::Event &event)
{
    if(event.type == sf::Event::KeyReleased)
        if(event.key.code == sf::Keyboard::Tab)
        {
            show_turns = !show_turns;
            if(show_turns) info.addItem("turns left", turns);
            else info.removeItem("turns left");
        }
        else if(event.key.code == sf::Keyboard::Return)
            edit(object); //otwiera okienko edycji zmiennych
    if(event.type == sf::Event::TextEntered)
    {
        text += (char)event.text.unicode;
    }
}

void Test::sync()
{
    //tu robimy synchronizacje z serwerem
    turns = turns_left();

    //rysowanie prostokata na ekranie
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(50, 50));
    //mozna tez zrobic shape.setFillColor(sf::Color(r, g, b));
    shape.setFillColor(sf::Color::White);
    shape.rotate(75);
    shape.setPosition(500, 300);
    //nie trzeba wywolywac wszystkich funkcji powyzej, wtedy niektore parametry (obrot, kolor itp) beda domyslne
    addDrawable(shape);

    //dalej mozna uzyc tego samego obiektu shape do rysowania kolejnego prostokata)
    shape.setPosition(500, 100);
    shape.setFillColor(sf::Color::Red);
    addDrawable(shape);
    hex.draw(*this);
}

void Test::firstSync()
{
    sync();
}

void Test::leftClick(sf::Vector2f position)
{
    auto p = hex.getHex(position);
    if(p.first != -1)
        hex.setColor(p.first, p.second, sf::Color::Red);
}

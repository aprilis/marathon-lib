#include "EditorExample.h"

const int SQUARES_N = 4;

int turns = 0;

EditorExample::EditorExample(int width, int height) : Game(width, height, "Editor Example")
{
    for(int i = 0; i < SQUARES_N; i++)
        squares.emplace_back(100 + i * 60, 100);
    info.addFunction("instrukcja", []() { return "nacisnij przycisk od 1 do 4 zeby edytowac wybrany kwadrat"; });
    info.addItem("turns", turns);
}

void EditorExample::sync()
{
    turns++;
    for(auto &s: squares)
        addDrawable(s.getShape());
}

void EditorExample::myProcessEvent(const sf::Event &event)
{
    if(event.type == sf::Event::TextEntered)
    {
        char code = event.text.unicode;
        if(code >= '1' && code < '1' + SQUARES_N)
            edit(squares[code - '1']); //ta funkcja pokazuje okienko w ktorym mozna edytowac obiekty
    }
}



#ifndef TEST_H
#define TEST_H

#include "Game.h"
#include "PropertiesEditor.h"

//tego nie musicie ogarniac, to nie jest takie wazne
struct TestObject
{
    int a = 0, b = 0;
    string s = "a"; 
  
    PropertiesEditor& getPropertiesEditor()
    {
        //tutaj tworzy sie okienko w ktorym mozna edytowac zmienne
        static PropertiesEditor editor;
        static bool init;
        if(!init)
        {
            init = true;
            editor.add(DEFAULT_PROPERTY(a));
            editor.add(DEFAULT_PROPERTY(b));
            editor.add(DEFAULT_PROPERTY(s));
        }
        editor.setObject(this);
        return editor;
    }
};

//to jest najwazniejsza klasa w programie
class Test : public Game
{
protected:
    //tu deklarujemy funkcje z klasy Game ktore chcemy zmienic
    void draw();

    void myProcessEvent(const sf::Event &event);

    void leftClick(sf::Vector2f position);

    void sync();

    void firstSync();

    TestObject object;

    bool show_turns = false;

    int turns = 0;

    string text;

public:
    Test() = default;

    Test(int width, int height);
};

#endif // TEST_H

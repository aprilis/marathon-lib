#ifndef EDITOREXAMPLE_H
#define EDITOREXAMPLE_H

//Przyklad pokazujacy uzycie okienkowego edytora zmiennych

#include "../lib/Game.h"
#include "../lib/PropertiesEditor.h"
#include "../lib/Settings.h"
#include "../lib/Common.h"
#include <vector>
using namespace std;

struct EditableSquare
{
    float rotation = 0;
    float size = 50;
    float px, py;
    bool border = false;
    sf::Color color = sf::Color::Red;

    EditableSquare(float x = 0, float y = 0) : px(x), py(y) { }

    sf::RectangleShape getShape()
    {
        auto rect = makeRectangle(size, size, px, py, color);
        rect.rotate(rotation);
        if(border)
        {
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(4);
        }
        return rect;
    }

    PropertiesEditor& getPropertiesEditor()
    {
        //tutaj tworzy sie okienko w ktorym mozna edytowac zmienne
        static PropertiesEditor editor;
        static bool init;
        if(!init)
        {
            init = true;

            //zmienne typu int, float, string, bool itd jest latwo dodac
            editor.add(DEFAULT_PROPERTY(rotation));
            editor.add(DEFAULT_PROPERTY(size));
            editor.add(DEFAULT_PROPERTY(border));

            //w przypadku takich rzeczy jak sf::Color trzeba troche wiecej napisac
            editor.add(COMBOBOX_PROPERTY(color)->add("white", sf::Color::White)
                                               ->add("red", sf::Color::Red)
                                               ->add("green", sf::Color::Green)
                                               ->add("blue", sf::Color::Blue));
        }
        editor.setObject(this);
        return editor;
    }
};

class EditorExample : public Game
{
    vector<EditableSquare> squares;

    void myProcessEvent(const sf::Event &event);

    void sync();

public:
    EditorExample(int width, int height);
};

#endif // EDITOREXAMPLE_H


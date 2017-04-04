#ifndef INFO_H
#define INFO_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Info
{
    static sf::Font font;

    vector<string> items;

public:
    static void loadFont(string filename) { font.loadFromFile(filename); }

    static sf::Font& getFont() { return font; }

    void addItem(string item);

    void popItem() { items.pop_back(); }

    void clear();

    void draw(sf::RenderWindow &window);

    void log(ostream &o);
};

#endif // INFO_H

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
    vector<string> items;

public:
    void addItem(string item);

    void popItem() { items.pop_back(); }

    void clear();

    void draw(sf::RenderWindow &window);

    void log(ostream &o);
};

#endif // INFO_H

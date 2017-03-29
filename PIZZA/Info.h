#ifndef INFO_H
#define INFO_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <string>
using namespace std;

class Info
{
    static sf::Font font;

    vector<pair<string, function<string()>>> items;

public:
    static void loadFont(string filename) { font.loadFromFile(filename); }

    void addFunction(string label, function<string()> function)
    {
        items.emplace_back(label, function);
    }

    template<class T> void addItem(string label, T &variable)
    {
        addFunction(label, [&]() { return to_string(variable); });
    }

    void removeItem(string label);

    void draw(sf::RenderWindow &window);
};

template<> void Info::addItem<string>(string label, string &variable);

#endif // INFO_H

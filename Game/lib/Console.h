#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
using namespace std;

class Console
{
    vector<string> history;
    vector<string> output;

    string current;
    int currentPos = 0;
    int historyPos = 0;

    sf::Keyboard::Key trigger = sf::Keyboard::Tab;

    bool active = false;

    int lines = 10;

    int fontSize = 14;
    int gap = 5;

    sf::Color backgroundColor = { 0, 100, 0, 160 };

    vector<string> currentScreen();

    void setCurrent(string str);

public:
    ostringstream stdout;

    void setTrigger(sf::Keyboard::Key key) { trigger = key; }
    void setLines(int n) { lines = n; }
    void setFontSize(int n) { fontSize = n; }
    void setBackgroundcolor(sf::Color color) { backgroundColor = color; }

    void setActive(bool act) { active = act; }
    bool isActive() { return active; }

    pair<bool, string> processEvent(const sf::Event &event);

    void draw(sf::RenderWindow &window);
};

#endif // CONSOLE_H


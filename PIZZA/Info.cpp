#include "Info.h"

sf::Font Info::font;

void Info::draw(sf::RenderWindow &window)
{
    const sf::Color color = sf::Color::White;
    const int size = 14;
    const int gap = 20;
    sf::Text text;
    text.setFont(font);
    text.setColor(color);
    text.setCharacterSize(size);
    sf::Vector2f pos(gap, gap);
    for(auto item: items)
    {
        text.setPosition(pos);
        text.setString(item.first + ": " + item.second());
        window.draw(text);
        pos.y += font.getLineSpacing(size);
    }
}

template<> void Info::addItem<string>(string label, string &variable)
{
    addFunction(label, [&]() { return variable; });
}

void Info::removeItem(string label)
{
    for(int i = 0; i < items.size(); i++)
        if(items[i].first == label)
        {
            items.erase(items.begin() + i);
            i--;
        }
}

bool Info::hasItem(string label)
{
    for(const auto &i: items)
        if(i.first == label)
            return true;
    return false;
}

void Info::clear()
{
    items.clear();
}

#include "Info.h"
#include "Common.h"

void Info::draw(sf::RenderWindow &window)
{
    const sf::Color color = sf::Color::White;
    const int size = 14;
    const int gap = 20;
    sf::Text text;
    text.setFont(commonFont);
    text.setColor(color);
    text.setCharacterSize(size);
    sf::Vector2f pos(gap, gap);
    for(const auto &item: items)
    {
        text.setPosition(pos);
        text.setString(item);
        window.draw(text);
        pos.y += commonFont.getLineSpacing(size);
    }
}

void Info::addItem(string label)
{
    items.push_back(label);
}

void Info::clear()
{
    items.clear();
}

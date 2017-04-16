#include "Common.h"
#include "Config.h"
#include <cmath>
#include <iostream>

sf::Font commonFont;
bool isCommonFontLoaded = commonFont.loadFromFile(FONT_PATH);

inline double length(const double &x, const double &y)
{
    return sqrt(x * x + y * y);
}

inline double lengthSquare(const double &x, const double &y)
{
    return x * x + y * y;
}

inline double dist(const double &x1, const double &y1, const double &x2, const double &y2)
{
    return length(x1 - x2, y1 - y2);
}

inline double distSquare(const double &x1, const double &y1, const double &x2, const double &y2)
{
    return lengthSquare(x1 - x2, y1 - y2);
}

sf::CircleShape makeCircle(float radius, float x, float y, sf::Color fillColor)
{
    sf::CircleShape shape(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setFillColor(fillColor);
    return shape;
}

sf::RectangleShape makeRectangle(float width, float height, float x, float y, sf::Color fillColor)
{
    sf::RectangleShape shape(sf::Vector2f(width, height));
    shape.setOrigin(width / 2, height / 2);
    shape.setPosition(x, y);
    shape.setFillColor(fillColor);
    return shape;
}

sf::RectangleShape makeLine(float x1, float y1, float x2, float y2, float thickness, sf::Color fillColor)
{
    auto length = dist(x1, y1, x2, y2) + thickness;
    sf::RectangleShape shape(sf::Vector2f(length, thickness));
    shape.setOrigin(thickness / 2, thickness / 2);
    shape.setPosition(x1, y1);
    shape.setRotation(atan2(y2 - y1, x2 - x1) * 180 / M_PI);
    shape.setFillColor(fillColor);
    return shape;
}

sf::Text makeText(string caption, int fontSize, float x, float y, sf::Color color)
{
    sf::Text text(sf::String(caption), commonFont);
    text.setCharacterSize(fontSize);
    auto rect = text.getLocalBounds();
    text.setOrigin(rect.width / 2, rect.height / 2);
    text.setPosition(x, y);
    text.setColor(color);
    return text;
}

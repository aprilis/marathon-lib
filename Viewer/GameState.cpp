#include "GameState.h"
#include "Config.h"
#include "Info.h"
#include <iostream>

ostream& operator<<(ostream &o, const sf::Vector2f &vec)
{
    o << vec.x << " " << vec.y;
    return o;
}

ostream& operator<<(ostream &o, const sf::Color &col)
{
    o << col.toInteger();
    return o;
}

istream& operator>>(istream &i, sf::Vector2f &vec)
{
    i >> vec.x >> vec.y;
    return i;
}

istream& operator>>(istream &i, sf::Color &col)
{
    sf::Uint32 code;
    i >> code;
    col = sf::Color(code);
    return i;
}

GameState::GameState(string path, Info &info) : in(path), inf(info)
{
    turns.push_back(0);
#ifdef STREAM_WINDOW
    window = new StreamWindow({"out", "err"});
#endif
}

GameState::~GameState()
{
#ifdef STREAM_WINDOW
    delete window;
#endif
}

bool GameState::nextTurn()
{
    drawables.clear();
    current_out.clear();
    current_err.clear();
    int r;
    do
    {
        r = readLine();
    } while(r == 0);
    auto pos = in.tellg();
    if(r == 1 && turns.back() < pos)
        turns.push_back(pos);
    if(r == 2 && turns.size() > 1)
        prevTurn();
    update();
    return r != 2;
}

bool GameState::prevTurn()
{
    if(in.eof())
    {
        in.clear();
        if(turns.size() < 2) return false;
        in.seekg(turns[turns.size() - 2]);
    }
    else
    {
        auto it = lower_bound(turns.begin(), turns.end(), in.tellg());
        if(it - turns.begin() <= 1) return false;
        in.seekg(*(it - 2));
    }
    nextTurn();
    return true;
}

void GameState::update()
{
#ifdef STREAM_WINDOW
    window->setText({ current_out, current_err });
#endif
}

sf::Drawable* GameState::readCircle()
{
    auto circle = new sf::CircleShape();
    float rad;
    int count;
    readShape(*circle);
    in >> rad >> count;
    circle->setRadius(rad);
    circle->setPointCount(count);
    return circle;
}

sf::Drawable* GameState::readRect()
{
    auto rect = new sf::RectangleShape();
    sf::Vector2f size;
    readShape(*rect);
    in >> size;
    rect->setSize(size);
    return rect;
}

sf::Drawable* GameState::readConvex()
{
    auto convex = new sf::ConvexShape();
    int count;
    readShape(*convex);
    in >> count;
    convex->setPointCount(count);
    for(int i = 0; i < count; i++)
    {
        sf::Vector2f point;
        in >> point;
        convex->setPoint(i, point);
    }
    return convex;
}

sf::Drawable* GameState::readText()
{
    auto text = new sf::Text();
    text->setFont(Info::getFont());
    sf::Color color;
    string str;
    unsigned charSize;
    in >> charSize >> color;
    getline(in, str);
    text->setCharacterSize(charSize);
    text->setColor(color);
    text->setString(sf::String(str));
    return text;
}

void GameState::readShape(sf::Shape &shape)
{
    sf::Color fillColor, outlineColor;
    float outlineThickness;
    in >> fillColor >> outlineColor >> outlineThickness;
    shape.setFillColor(fillColor);
    shape.setOutlineColor(outlineColor);
    shape.setOutlineThickness(outlineThickness);
}

sf::Transform GameState::readTransform()
{
    float tab[9];
    for(int i = 0; i < 9; i++)
        in >> tab[i];
    return sf::Transform(tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6], tab[7], tab[8]);
}

void GameState::draw(sf::RenderWindow &win)
{
    for(const auto &d: drawables)
        win.draw(*d.first, sf::RenderStates(d.second));
}

int GameState::readLine()
{
    string key;
    in >> key;
    in.ignore(1);
    if(in.eof()) return 2;
    if(key == "next_turn") return 1;
    else if(key == "out")
    {
        string str;
        getline(in, str);
        current_out += str + '\n';
    }
    else if(key == "err")
    {
        string str;
        getline(in, str);
        current_err += str + '\n';
    }
    else if(key == "info")
    {
        string str;
        getline(in, str);
        inf.addItem(str);
    }
    else
    {
        auto transform = readTransform();
        sf::Drawable *drawable;
        if(key == "text") drawable = readText();
        else if(key == "circle") drawable = readCircle();
        else if(key == "rect") drawable = readRect();
        else if(key == "convex") drawable = readConvex();
        else cerr << "unknown key: " << key << endl;
        drawables.emplace_back(unique_ptr<sf::Drawable>(drawable), transform);
    }
    return 0;
}

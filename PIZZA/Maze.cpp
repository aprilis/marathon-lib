#include "Maze.h"
#include "wrapper.h"

map<char, sf::Color> colors = { { 'F', sf::Color::Green },
                                { 'S', sf::Color::Yellow },
                                { 'E', sf::Color::Red },
                                { 'W', sf::Color::Cyan } };

Maze::Maze(int width, int height) : Game(width, height)
{
    info.addItem("turns left", turnsLeft);
    moveCamera(0, 0);
    showOutputWindow();
}

void Maze::draw()
{
}

void Maze::sync()
{
    const int scale = 20;
    sf::RectangleShape shape(sf::Vector2f(scale, scale));

    send_message("SCAN");
    int n;
    cin >> n;
    while(n--)
    {
        string str;
        int x, y;
        cin >> str >> x >> y;
        merr << str << " " << x << " " << y << "\n";
        shape.setPosition(x * scale, y * scale);
        shape.setFillColor(isdigit(str[0]) ? sf::Color::Magenta : colors[str[0]]);
        addDrawable(shape);
        if(isdigit(str[0]))
        {
            sf::Text text;
            text.setFont(Info::getFont());
            text.setCharacterSize(scale / 2);
            text.setPosition(x * scale, y * scale);
            text.setString(sf::String(str));
            text.setColor(sf::Color::White);
            addDrawable(text);
        }
    }
}

void Maze::sendCommands()
{
    if(mx != 0 || my != 0)
    {
        mout << "MOVE " << mx << " " << my;
        send_message();
        mx = my = 0;
    }
}

void Maze::myProcessEvent(const sf::Event &event)
{
    if(event.type == sf::Event::KeyReleased)
        switch(event.key.code)
        {
        case sf::Keyboard::Left:
            mx = -1;
            my = 0;
            break;
        case sf::Keyboard::Right:
            mx = 1;
            my = 0;
            break;
        case sf::Keyboard::Up:
            mx = 0;
            my = -1;
            break;
        case sf::Keyboard::Down:
            mx = 0;
            my = 1;
            break;
        case sf::Keyboard::O:
            showOutputWindow();
            break;
        }
}

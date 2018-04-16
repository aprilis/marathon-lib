#include "Console.h"
#include "Common.h"
#include <iostream>
#include <set>

static const string prompt = ">> ";

vector<string> split(string str, char sep = '\n')
{
    string buf = "";
    vector<string> ans;
    for(auto c: str)
        if(c == sep)
        {
            ans.push_back(buf);
            buf = "";
        }
        else buf += c;
   if(buf != "")
       ans.push_back(buf);
   return ans;
}

vector<string> Console::currentScreen()
{
    vector<string> result = output;
    auto lastOut = split(stdout.str());
    result.insert(result.end(), lastOut.begin(), lastOut.end());
    result.push_back(prompt + current);
    if(result.size() > lines)
        result.erase(result.begin(), result.begin() + result.size() - lines);
    return result;
}

pair<bool, string> Console::processEvent(const sf::Event &event)
{
    set<char> ignored = { 8, 9, 27, 127 }; //backspace, tab, escape, delete
    if(active && event.type == sf::Event::TextEntered)
    {
        auto unicode = event.text.unicode;
        if(unicode < 128)
        {
            if(unicode == 13) //enter
            {
                output = currentScreen();
                stdout.str("");

                auto result = current;
                history.push_back(result);
                setCurrent("");
                historyPos = history.size();
                return { true, result };
            }
            if(unicode == 8) //backspace
                if(currentPos > 0)
                {
                    current.erase(current.begin() + currentPos - 1);
                    currentPos--;
                }
            if(unicode == 127)
                if(currentPos < current.size())
                    current.erase(current.begin() + currentPos);

            if(!ignored.count(unicode))
            {
                current.insert(current.begin() + currentPos, unicode);
                currentPos++;
            }

            return { true, "" };
        }
    }
    if(event.type == sf::Event::KeyReleased && event.key.code == trigger)
    {
        active = !active;
        return { true, "" };
    }
    if(active && event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Left)
        {
            if(currentPos > 0) currentPos--;
            return { true, "" };
        }
        if(event.key.code == sf::Keyboard::Right)
        {
            if(currentPos < current.size()) currentPos++;
            return { true, "" };
        }
        if(event.key.code == sf::Keyboard::Up)
        {
            if(historyPos > 0)
                setCurrent(history[--historyPos]);
            return { true, "" };
        }
        if(event.key.code == sf::Keyboard::Down)
        {
            if(historyPos < history.size())
                setCurrent(++historyPos < history.size() ? history[historyPos] : "");
            return { true, "" };
        }
    }
    return { false, "" };
}

void Console::draw(sf::RenderWindow &window)
{
    if(!active) return;
    static const int gap = 10;

    vector<string> screen = currentScreen();
    const auto &font = commonFont;
    auto height = screen.size() * font.getLineSpacing(fontSize) + gap * 2;
    auto windowHeight = window.getSize().y;

    sf::RectangleShape background;
    background.setFillColor(sf::Color(0, 100, 0, 160));
    background.setSize({ window.getSize().x, height });
    background.setPosition({ 0, windowHeight - height });
    window.draw(background);

    height -= gap;
    for(auto &s: screen)
    {
        sf::String str(s);
        if(&s == &screen.back())
            str.insert(currentPos + prompt.size(), sf::String((sf::Uint32)0x02C5));
        sf::Text text(str, font, fontSize);
        text.setPosition(gap, windowHeight - height);
        window.draw(text);
        height -= font.getLineSpacing(fontSize);
    }
}

void Console::setCurrent(string str)
{
    current = str;
    currentPos = str.size();
}

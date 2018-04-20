#include "GameState.h"
#include "Log.h"
#include "Config.h"
#include <SFML/System.hpp>
#include <GL/gl.h>
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

stringstream GameState::out_stream;
stringstream GameState::err_stream;
ofstream GameState::log;

GameState::GameState(string title)
{
#ifdef SAVE_GAME
    openLog(log, "games");
#endif
    static bool init = false;
    if(!init)
    {
        init = true;
        mout.addStream(out_stream);
        merr.addStream(err_stream);
    }
    out_stream.str("");
    err_stream.str("");
#ifdef STREAM_WINDOW
    window = new StreamWindow(title, {"out", "err"});
#endif

    for(auto &f: faceShift)
    {
        const float SHIFT = 0.4;
        f.x = (float)rand() / RAND_MAX * SHIFT + (1 - SHIFT);
        f.y = (float)rand() / RAND_MAX * SHIFT + (1 - SHIFT);
        f.z = (float)rand() / RAND_MAX * SHIFT + (1 - SHIFT);
    }
}

GameState::~GameState()
{
#ifdef STREAM_WINDOW
    delete window;
#endif
}

void GameState::showWindow()
{
#ifdef STREAM_WINDOW
    window->show();
#endif
}

void GameState::nextTurn()
{
    current_out = out_stream.str();
    current_err = err_stream.str();
#ifdef SAVE_GAME
    log << "next_turn\n";
    logStream("out", current_out);
    logStream("err", current_err);
#endif
    out_stream.str("");
    err_stream.str("");
}

void GameState::update()
{
#ifdef STREAM_WINDOW
    window->setText({ current_out, current_err });
#endif
}

void GameState::logStream(const string &name, const string &str)
{
    size_t i = 0;
    while(true)
    {
        size_t ni = str.find('\n', i);
        log << name << " " << str.substr(i, ni - i) << "\n";
        if(ni == string::npos) break;
        i = ni + 1;
    }
}

void GameState::logObject(const sf::CircleShape &obj)
{
    log << "circle ";
    logShape(obj);
    log << obj.getRadius() << " " << obj.getPointCount();
}

void GameState::logObject(const sf::RectangleShape &obj)
{
    log << "rect ";
    logShape(obj);
    log << obj.getSize();
}

void GameState::logObject(const sf::ConvexShape &obj)
{
    log << "convex ";
    logShape(obj);
    log << obj.getPointCount() << " ";
    for(int i = 0; i < obj.getPointCount(); i++)
        log << obj.getPoint(i) << " ";
}

void GameState::logObject(const sf::Text &obj)
{
    log << "text ";
    logTransform(obj.getTransform());
    string s = obj.getString().toAnsiString();
    for(auto &x: s)
        if(x == '\n') x = ' ';
    log << obj.getCharacterSize() << " " << obj.getColor() << " " << s;
}

void GameState::logShape(const sf::Shape &shape)
{
    logTransform(shape.getTransform());
    log << shape.getFillColor() << " " << shape.getOutlineColor() << " " << shape.getOutlineThickness() << " ";
}

void GameState::logTransform(const sf::Transform &transform)
{
    static int ord[] = { 0, 3, -1, 6, 1, 4, -1, 7, -1, -1, -1, -1, 2, 5, -1, 8 };
    auto mat = transform.getMatrix();
    float ans[9];
    for(int i = 0; i < 16; i++)
        if(ord[i] != -1) ans[ord[i]] = mat[i];
    for(int i = 0; i < 9; i++)
        log << ans[i] << " ";
}

void GameState::addCube(sf::Vector3f position, sf::Color color, float size)
{
    addCube(position, color, { size, size, size });
}

void GameState::addCube(sf::Vector3f position, sf::Color color, sf::Vector3f size)
{
    cubes.push_back({ position, color, size });
}

void GameState::draw(sf::RenderWindow &win)
{
    for(const auto &d: drawables)
        win.draw(*d);
}

static void glVertex3f(const sf::Vector3f &vec)
{
    glVertex3f(vec.x, vec.y, vec.z);
}

static void drawSquare(const sf::Vector3f &corner, const sf::Vector3f &v1, const sf::Vector3f &v2)
{
    glVertex3f(corner);
    glVertex3f(corner + v1);
    glVertex3f(corner + v1 + v2);
    glVertex3f(corner + v2);
}

static void glColor(sf::Color col, sf::Vector3f noise)
{
    glColor3ub(min(255, (int)(col.r * noise.x)), min(255, (int)(col.g * noise.y)), min(255, (int)(col.b * noise.z)));
}

void GameState::draw3D(sf::RenderWindow &win, Transform transform)
{
    if(!cubes.empty())
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for(auto c: cubes)
        {
            auto s = c.size;
            auto col = c.color;
            sf::Vector3f c1 { 0, 0, 0 }, c2 = s;

            glPushMatrix();
            glTranslatef(c.position.x, c.position.y, c.position.z);
            glMultMatrixf(transform.inverse().matrix);

            glBegin(GL_QUADS);

            glColor(col, faceShift[0]);
            drawSquare(c1, { 0, s.y, 0 }, { s.x, 0, 0 });

            glColor(col, faceShift[1]);
            drawSquare(c1, { s.x, 0, 0 }, { 0, 0, s.z });

            glColor(col, faceShift[2]);
            drawSquare(c1, { 0, 0, s.z }, { 0, s.y, 0 });

            glColor(col, faceShift[3]);
            drawSquare(c2, { -s.x, 0, 0 }, { 0, -s.y, 0 });

            glColor(col, faceShift[4]);
            drawSquare(c2, { 0, 0, -s.z }, { -s.x, 0, 0 });

            glColor(col, faceShift[5]);
            drawSquare(c2, { 0, -s.y, 0 }, { 0, 0, -s.z });

            glEnd();

            glPopMatrix();
        }
    }
}

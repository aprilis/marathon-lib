#include <iostream>
#include <QApplication>
#include <clocale>
#include "Config.h"
#include "Game.h"
using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        cout << "Usage: ./Viewer <path_to_file>" << endl;
        return 0;
    }

    QApplication app(argc, argv);
    setlocale(LC_NUMERIC,"C");

    Info::loadFont("font.ttf");
    Game game(800, 600, argv[1]);
    game.run();
    return 0;
}


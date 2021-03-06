#include "lib/Wrapper.h"
#include "lib/Config.h"
#include "lib/Log.h"
#include "lib/StdinLog.h"
#include "examples/Maze.h"
#include "examples/GeneralExample.h"
#include "examples/HexMapExample.h"
#include "examples/EditorExample.h"
#include "examples/3DExample.h"
#include "MyGame.h"
#include <clocale>
#include <iostream>
#include <QApplication>
#include <SFML/Audio.hpp>
using namespace std;

int main(int argc, char *argv[])
{
    int port = 10000;
    setLogPrefix(to_string(port) + "_");

    QApplication app(argc, argv);
    setlocale(LC_NUMERIC,"C");

    connect("tr.contest.pizza", port, "team26", "8372d2fdca");
    ofstream logger, stderrLogger;
    merr.addStream(stderrLogger);
    mout.addStream(logger);
    StdinLog inLog;
    inLog.start(logger);

    while(true)
    {
        try
        {
            openLog(logger, "logs");
            openLog(stderrLogger, "stderr");

            //ThreeDExample game(800, 600);
            //GeneralExample game(800, 600);
            //HexMapExample game(800, 600);
            //EditorExample game(800, 600);
            Maze game(800, 600);
            //MyGame game(800, 600, "Deadline24 " + to_string(port));
            game.run();
        }
        catch(...)
        {
            merr << "restarting...\n";
            sleep(1);
        }
        logger << flush;
        stderrLogger << flush;
    }

    return 0;
}


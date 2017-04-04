#include <iostream>
#include "wrapper.h"
#include <QApplication>
#include "Maze.h"
#include "Test.h"
#include <clocale>
#include "Config.h"
#include "Log.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setlocale(LC_NUMERIC,"C");

    connect("test.natodia.net", 10000, "team60", "157159331f");
    Info::loadFont("font.ttf");
    ofstream logger;
    merr.addStream(logger);
    mout.addStream(logger);
    while(true)
    {
        try
        {
            open_log(logger, "logs");
            Maze t(800, 600);
            t.run();
        }
        catch(...)
        {
            merr << "restarting...\n";
            sleep(1);
        }
        logger << flush;
    }

    return 0;
}


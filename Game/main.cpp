#include "lib/Wrapper.h"
#include "lib/Config.h"
#include "lib/Log.h"
#include "examples/Maze.h"
#include "examples/GeneralExample.h"
#include "examples/HexMapExample.h"
#include "examples/EditorExample.h"
#include <clocale>
#include <iostream>
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setlocale(LC_NUMERIC,"C");

    connect("test.natodia.net", 10000, "team60", "157159331f");
    ofstream logger;
    merr.addStream(logger);
    mout.addStream(logger);
    while(true)
    {
        try
        {
            open_log(logger, "logs");
            //GeneralExample game(800, 600);
            //HexMapExample game(800, 600);
            EditorExample game(800, 600);
            //Maze game(800, 600);
            game.run();
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


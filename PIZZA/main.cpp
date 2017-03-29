#include <iostream>
#include "wrapper.h"
#include <QApplication>
#include "Test.h"
#include <clocale>
#include "Config.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setlocale(LC_ALL,"C");

    connect("universum.dl24", 20005, "team3", "lfnhsxjojs");
    Info::loadFont("font.ttf");

    while(true)
    {
        try
        {
            Test t(800, 600);
            t.run();
        }
        catch(...)
        {
            cerr << "restarting..." << endl;
            sleep(1);
        }
    }

    return 0;
}


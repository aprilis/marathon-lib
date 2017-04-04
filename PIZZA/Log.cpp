#include "Log.h"
#include <ctime>
#include <fstream>

MultiStream mout = { &cout };
MultiStream merr = { &cerr };

void open_log(ofstream &of, string dir)
{
    system(("mkdir " + dir).c_str());
    if(of.is_open()) of.close();
    char time_rep[100];
    auto tm = time(NULL);
    strftime(time_rep, 100, "%H_%M_%S", localtime(&tm));
    of.open(dir + "/" + time_rep + ".log");
}

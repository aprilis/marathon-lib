#ifndef STDINLOG_H
#define STDINLOG_H

#include <fstream>
#include <string>
#include <thread>
using namespace std;

class StdinLog
{
    FILE *input, *output;

    ostream *out;

    string pref;

    thread *th;

    void loop();

public:
    StdinLog(string prefix = "INPUT: ") : pref(prefix) { }

    void start(ostream &log);
};

#endif // STDINLOG_H


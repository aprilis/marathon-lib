#include "StdinLog.h"
#include <cstdio>
#include <unistd.h>
#include <thread>

void StdinLog::start(ostream &log)
{
    out = &log;

    int fd = dup(STDIN_FILENO);
    input = fdopen(fd, "r");

    int pipefd[2];
    pipe(pipefd);
    dup2(pipefd[0], STDIN_FILENO);
    output = fdopen(pipefd[1], "w");

    th = new thread(&StdinLog::loop, this);
}

void StdinLog::loop()
{
    const int N = 10000;
    char buf[N+1];
    while(true)
    {
        fgets(buf, N, input);
        fprintf(output, buf);
        *out << pref + buf;
    }
}

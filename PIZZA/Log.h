#ifndef LOG_H
#define LOG_H

#include <vector>
#include <iostream>
using namespace std;

class MultiStream
{
    vector<ostream*> out;

public:
    MultiStream() = default;
    MultiStream(initializer_list<ostream*> list) : out(list) { }

    void addStream(ostream &str) { out.push_back(&str); }

    void clear() { out.clear(); }

    template<class T> MultiStream& operator<<(const T& obj)
    {
        for(auto o: out)
            (*o) << obj;
        return *this;
    }

    void flush()
    {
        for(auto o: out)
            (*o) << std::flush;
    }
};

extern MultiStream mout;
extern MultiStream merr;

void open_log(ofstream &of, string dir);

#endif // LOG_H

#include "wrapper.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <unistd.h>
#include "Config.h"

CTcpFwd *tcpfwd = nullptr;

//tu trzeba dopisac kody ignorowanych bledow
set<int> ignored_errors = {108, 109, 105, 6, 107};

bool checkOK()
{
#ifdef TCP
    string s;
    cin >> s;
    if(s == "OK")
        return true;
    else if(s == "ERR")
    {
        int code;
        cin >> code;
        getline(cin, s);
        if(code == 6) //commands limit reached
        {
            getline(cin, s);
            checkOK();
            return false;
        }
        if(ignored_errors.count(code)) return false;
        cerr << "ERROR" << code << s << endl;
#ifdef THROW_EXCEPTIONS
        throw make_pair(code, s);
#endif
    }
    else
    {
        cerr << "NIE WCZYTAŁEŚ CAŁEJ POPRZEDNIEJ ODPOWIEDZI DEBILU!!!" << endl;
        cerr << s << " ";
        getline(cin, s);
        cout << s << endl;
        throw make_pair(-3, s);
    }
#endif
    return true;
}

void connect(string host, int port, string login, string password)
{
#ifdef TCP
    if(tcpfwd) delete tcpfwd;
    tcpfwd = new CTcpFwd("deadline", host.c_str(), port);
    tcpfwd->SwitchStdin("deadline");
    tcpfwd->SwitchStdout("deadline");
    string s;
    cin >> s;
    if(s != "LOGIN")
    {
        cerr << "Error while logging in: " << s << endl;
        throw make_pair(-1, s);
    }
    cout << login << endl;
    cin >> s;
    if(s != "PASS")
    {
        cerr << "Error while logging in: " << s << endl;
        throw make_pair(-2, s);
    }
    cout << password << endl;
    checkOK();
    cerr << "Logged in successfully" << endl;
#endif
}

bool send_message(string message)
{
    cerr << "sending:" << message << endl;
    cout << message << endl;
    return checkOK();
}

void wait()
{
#ifdef TCP
    send_message("WAIT");
    checkOK();
#endif
}

int turns_left()
{
#if defined TCP && defined TURNS_LEFT_COMMAND
    send_message(TURNS_LEFT_COMMAND);
    int turns;
    cin >> turns;
    return turns;
#else
    return 0;
#endif

}

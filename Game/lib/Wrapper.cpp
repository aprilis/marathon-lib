#include "Wrapper.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <unistd.h>
#include "Config.h"

CTcpFwd *tcpfwd = nullptr;

//tu trzeba dopisac kody ignorowanych bledow
set<int> ignored_errors = { };

bool checkOK()
{
#ifdef TCP
    string s;
    cin >> s;
    if(s == "OK")
        return true;
    else if(s == ERROR_STRING)
    {
        int code;
        cin >> code;
        getline(cin, s);
        if(ignored_errors.count(code)) return false;
        merr << "ERROR" << code << s << "\n";
#ifdef THROW_EXCEPTIONS
        throw make_pair(code, s);
#endif
    }
    else
    {
        merr << "NIE WCZYTAŁEŚ CAŁEJ POPRZEDNIEJ ODPOWIEDZI DEBILU!!!\n";
        merr << s << " ";
        getline(cin, s);
        mout << s << "\n";
        throw make_pair(-3, s);
    }
#endif
    return true;
}

void connect(string host, int port, string login, string password)
{
#ifdef TCP
    if(tcpfwd) delete tcpfwd;
    tcpfwd = new CTcpFwd("marathon", host.c_str(), port);
    tcpfwd->SwitchStdin("marathon");
    tcpfwd->SwitchStdout("marathon");
    string s;
    cin >> s;
    if(s != "LOGIN")
    {
        merr << "Error while logging in: " << s << "\n";
        throw make_pair(-1, s);
    }
    cout << login << endl;
    cin >> s;
    if(s != "PASS")
    {
        merr << "Error while logging in: " << s << "\n";
        throw make_pair(-2, s);
    }
    cout << password << endl;
    checkOK();
    merr << "Logged in successfully" << "\n";
#endif
}

bool sendMessage(string message)
{
    mout << message << "\n";
    cout << flush;
    return checkOK();
}

void wait()
{
#ifdef TCP
    sendMessage("WAIT");
    checkOK();
#endif
}

int turnsLeft()
{
#if defined TCP && defined TURNS_LEFT_COMMAND
    sendMessage(TURNS_LEFT_COMMAND);
    int turns;
    cin >> turns;
    return turns;
#else
    return 0;
#endif
}

#include "CTcpFwd.h"
#include "Log.h"
#include <string>
#include <vector>
using namespace std;

void connect(string host, int port, string login, string password);

bool send_message(string message = string());

void wait();

int turns_left();

#include "CTcpFwd.h"
#include <string>
#include <vector>
using namespace std;

//tu jest pare przydatnych funkcji do komunikacji z serwerem (nieprzetestowane!!!)

void connect(string host, int port, string login, string password);

bool send_message(string message = string());

void wait();

int turns_left();

/*int current_turn();

int current_round();

double my_score();

vector<double> all_scores();

int my_place();
*/

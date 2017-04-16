#ifndef WRAPPER_H
#define WRAPPER_H


/*!
 * \file
 * \brief Contains a few useful functions for communication with server
 */

#include "CTcpFwd.h"
#include "Log.h"
#include <string>
#include <vector>
using namespace std;

/*!
 * \brief Initializes TCP connection. After calling this function, stdout sends output to the server and stdin reads input from it
 * \param host the name of the host
 * \param port the port number (integer)
 * \param login team login
 * \param password team password
 */
void connect(string host, int port, string login, string password);

/*!
 * \brief Writes message followed by endline to the stdout, and then checks if the response is OK or handles errors
 * \param message the message to write
 * \return true if server returned OK, false otherwise
 */
bool sendMessage(string message = string());

/*!
 * \brief Sends WAIT message and reads 2 OKs
 */
void wait();

/*!
 * \brief Calls TURNS_LEFT_COMMAND (defined in Config.h) and reads the response
 * \return the number of turns left
 */
int turnsLeft();

#endif

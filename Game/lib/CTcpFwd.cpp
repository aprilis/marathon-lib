/*
 * --=[ CTcpFwd:
 *    A cross platform STDIN/STDOUT ---> Socket forwarding engine
 *
 * Author: j00ru//vx
 * Date:   2010-04-03
 * E-mail: j00ru.vx@gmail.com
 * WWW:    http://j00ru.vexillium.org/
 *
 * LICENSE
 * Permission is hereby granted to use, copy, modify, and distribute this source code, 
 * or portions hereof, documentation and executables, for any purpose, without fee, 
 * subject to the following restrictions:
 * 
 * 1. The origin of this source code must not be misrepresented.
 *
 * 2. Altered versions must be plainly marked as such and must not be misrepresented 
 *    as being the original source.
 *
 * 3. This Copyright notice may not be removed or altered from any source or altered 
 *    source distribution.
 * 
 * This software is provided "AS IS". The author does not guarantee that this program works 
 * or is bug-free. The author takes no responsibility for any damage caused by this program.
 * Use at your own risk.
 */
#include <cstdio>
#include <cstdlib>
#include <string>
#include <stdarg.h>
#include "CTcpFwd.h"
using namespace std;

/* CTcpFwd::CTcpFwd
 *  - Constructor
 *  - Initializes Windows sockets, creates default stdin/out descriptors
 */
CTcpFwd::CTcpFwd()
{
  this->Init();
}

/* CTcpFwd::CTcpFwd
 * - Constructor
 * - Initializes the mechanism + connects to the specified host/port
 */
CTcpFwd::CTcpFwd
(const char* Host, int Port)
{
  this->Init();
  this->Connect("Default",Host,Port);
}

/* CTcpFwd::CTcpFwd
 * - Constructor
 * - Initializes the mechanism + creates a custom-named socket
 */
CTcpFwd::CTcpFwd
(const char* SessionName, const char* Host, int Port)
{
  this->Init();
  this->Connect(SessionName,Host,Port);
}

/* CTcpFwd::~CTcpFwd
 * - Destructor
 * - Clears the this->Sockets list and unitializes Windows Sockets
 */
CTcpFwd::~CTcpFwd()
{
  while(!this->Sockets.empty())
  {
    this->Disconnect(this->Sockets.begin()->first.c_str());
  }

#ifdef WIN32
  WSACleanup();
#endif
}


/* CTcpFwd::Init
 * - Internal initialization routine
 * - Creates default descriptors, turns the buffering off, initializes WSA
 */
void
CTcpFwd::Init()
{
  CTcpFwd::SocketInfo *StdIn, *StdOut;
  StdIn  = new SocketInfo;
  StdOut = new SocketInfo;

  memset(StdIn,0,sizeof(CTcpFwd::SocketInfo));
  memset(StdOut,0,sizeof(CTcpFwd::SocketInfo));

#ifdef WIN32
  HMODULE hMsvcrt = LoadLibrary("msvcrt.dll");
  this->__pioinfo = (typeof(this->__pioinfo))GetProcAddress(hMsvcrt,"__pioinfo");
  
  StdIn->Sock  = (SOCKET)_osfhnd(stdin->_file);
  StdIn->Flag  = _pioinfo(stdin->_file)->osfile;

  StdOut->Sock = (SOCKET)_osfhnd(stdout->_file);
  StdOut->Flag = _pioinfo(stdout->_file)->osfile;
#else
  StdIn->Sock  = dup(STDIN_FILENO);
  StdOut->Sock = dup(STDOUT_FILENO);
#endif

  this->Sockets[string("DefaultStdin")]  = StdIn;
  this->Sockets[string("DefaultStdout")] = StdOut;

  // turn off the IO buffering
  setvbuf(stdin,NULL,_IONBF,0);
  setvbuf(stdout,NULL,_IONBF,0);

#ifdef WIN32
  WSADATA wsdat;
  memset(&wsdat,0,sizeof(wsdat));
  WSAStartup(0x0101,&wsdat);
#endif
}


/* CTcpFwd::Connect
 * - Connects to a remote host and creates a named stream
 *
 * - Return value:
 *  * TRUE  on success
 *  * FALSE otherwise
 */
bool
CTcpFwd::Connect
(const char* SessionName, const char* Host, int Port)
{
  unsigned long ip;
  struct hostent *hostip;
  struct sockaddr_in sock_info;
  CTcpFwd::SocketInfo *Socket = new CTcpFwd::SocketInfo; 

  memset(Socket,0,sizeof(CTcpFwd::SocketInfo));

  ip = inet_addr(Host);
  if(ip == INADDR_NONE)
  {
    hostip = gethostbyname(Host);
    if(hostip==NULL)
      return false;
    memcpy(&ip,hostip->h_addr_list[0],4);
  }

#ifdef WIN32
  Socket->Sock = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,0);
#else
  Socket->Sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
#endif

  if(Socket->Sock == (unsigned)-1)
  {
    fprintf(stderr,"[-] socket() failed.\n");
    return false;
  }

  sock_info.sin_family      = AF_INET;
  sock_info.sin_addr.s_addr = ip;
  sock_info.sin_port        = htons(Port);
  memset(sock_info.sin_zero,0,sizeof(sock_info.sin_zero));

#ifdef WIN32
  if(WSAConnect(Socket->Sock,(struct sockaddr*)&sock_info,sizeof(struct sockaddr),NULL,NULL,NULL,NULL) == -1)
  {
    fprintf(stderr,"[-] WSAConnect() failed.\n");
    closesocket(Socket->Sock);
    return false;
  }

  BOOL DelayFlag = TRUE;
  if(setsockopt(Socket->Sock,IPPROTO_TCP,TCP_NODELAY,(const char*)&DelayFlag,sizeof(DelayFlag)))
  {
    fprintf(stderr,"[-] setsockopt() failed.\n");
    closesocket(Socket->Sock);
    return false;
  }

#else
  if(connect(Socket->Sock,(struct sockaddr*)&sock_info,sizeof(struct sockaddr)) == -1)
  {
    fprintf(stderr,"[-] connect() failed.\n");
    close(Socket->Sock);
    return false;
  }

  int DelayFlag = 1;
  if(setsockopt(Socket->Sock,IPPROTO_TCP,TCP_NODELAY,&DelayFlag,sizeof(DelayFlag))<0)
  {
    fprintf(stderr,"[-] setsockopt() failed.\n");
    close(Socket->Sock);
    return false;
  }
#endif

  Socket->Port = Port;
  Socket->Flag = FPIPE | FOPEN | FTEXT;
  strncpy(Socket->Host,Host,sizeof(Socket->Host));

  this->Sockets[string(SessionName)] = Socket;
  return true;
}



/* CTcpFwd::Disconnect
 * - Disconnects from a remote host and restores the default stdin/stdout handles
 *
 * - Return value:
 *  * TRUE  on success
 *  * FALSE otherwise
 */
bool
CTcpFwd::Disconnect(const char* SessionName)
{
  if(this->Sockets.find(string(SessionName)) == this->Sockets.end())
    return false;

  CTcpFwd::SocketInfo* Socket = this->Sockets[string(SessionName)];

#ifdef WIN32
  closesocket(Socket->Sock);
#else
  close(Socket->Sock);
#endif

  this->SwitchStdin("DefaultStdin");
  this->SwitchStdout("DefaultStdout");

  this->Sockets.erase(string(SessionName));
  delete Socket;

  return true;
}


/* CTcpFwd::SwitchStdin
 * - Switches the current STDIN stream to the specified name
 *
 * - Return value:
 *  * TRUE  on success
 *  * FALSE otherwise
 */
bool
CTcpFwd::SwitchStdin(const char* SessionName)
{
  if(this->Sockets.find(string(SessionName)) == this->Sockets.end())
    return false;

  CTcpFwd::SocketInfo* Socket = this->Sockets[string(SessionName)];

#ifdef WIN32
  if(__pioinfo == NULL)
  {
    fprintf(stderr,"[-] __pioinfo not found in msvcrt.dll!\n");
    return false;
  }

  _osfhnd(stdin->_file)          = (HANDLE)Socket->Sock;
  _pioinfo(stdin->_file)->osfile = Socket->Flag;
#else
  close(STDIN_FILENO);
  dup2(Socket->Sock,STDIN_FILENO);
#endif

  setvbuf(stdin,NULL,_IONBF,0);
  return true;
}


/* CTcpFwd::SwitchStdin
 * - Switches the current STDOUT stream to the specified name
 *
 * - Return value:
 *  * TRUE  on success
 *  * FALSE otherwise
 */
bool
CTcpFwd::SwitchStdout(const char* SessionName)
{
  if(this->Sockets.find(string(SessionName)) == this->Sockets.end())
    return false;

  CTcpFwd::SocketInfo* Socket = this->Sockets[string(SessionName)];

#ifdef WIN32
  if(__pioinfo == NULL)
  {
    fprintf(stderr,"[-] __pioinfo not found in msvcrt.dll!\n");
    return false;
  }

  _osfhnd(stdout->_file)          = (HANDLE)Socket->Sock;
  _pioinfo(stdout->_file)->osfile = Socket->Flag;
#else
  close(STDOUT_FILENO);
  dup2(Socket->Sock,STDOUT_FILENO);
#endif
  
  setvbuf(stdout,NULL,_IONBF,0);
  return true;
}


/* CTcpFwd::print
 * - Uses non-forwarded stderr stream to print debug messages on the screen
 *
 * - Return value:
 *  * The original value returned by fprintf
 */
int
CTcpFwd::print
(const char* format, ...)
{
  va_list ap;
  int ret;

  va_start(ap,format);
  ret = vfprintf(stderr,format,ap);
  fflush(stderr);
  va_end(ap);

  return ret;
}


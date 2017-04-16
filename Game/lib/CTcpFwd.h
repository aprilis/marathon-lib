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
#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <map>

#ifdef WIN32
  #include <windows.h>
  #include <winsock.h>
#else
  #include <cstring>
  #include <netinet/in.h>
  #include <netinet/tcp.h>
  #include <netdb.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <sys/socket.h>
  #include <unistd.h>
#endif

using namespace std;

// 
// Internal msvcrt structures from: \Microsoft Visual Studio 9.0\VC\crt\src\internal.h
//
#ifdef WIN32
  typedef struct {
          HANDLE osfhnd;    /* underlying OS file HANDLE */
          char osfile;        /* attributes of file (e.g., open in text mode?) */
          char pipech;        /* one char buffer for handles opened on pipes */
          int lockinitflag;
          CRITICAL_SECTION lock;
      }   ioinfo;

  #define IOINFO_L2E          5
  #define IOINFO_ARRAY_ELTS   (1 << IOINFO_L2E)
  #define _pioinfo(i) ( __pioinfo[(i) >> IOINFO_L2E] + ((i) & (IOINFO_ARRAY_ELTS - \
                                  1)) )
  #define _osfhnd(i)  ( _pioinfo(i)->osfhnd )
#endif


// 
// Internal msvcrt defs from: \Microsoft Visual Studio 9.0\VC\crt\src\internal.h
//
#define FOPEN           0x01    /* file handle open */
#define FEOFLAG         0x02    /* end of file has been encountered */
#define FCRLF           0x04    /* CR-LF across read buffer (in text mode) */
#define FPIPE           0x08    /* file handle refers to a pipe */
#define FNOINHERIT      0x10    /* file handle opened _O_NOINHERIT */
#define FAPPEND         0x20    /* file handle opened O_APPEND */
#define FDEV            0x40    /* file handle refers to device */
#define FTEXT           0x80    /* file handle is in text mode */


// TCP-Forwarding class
class CTcpFwd
{
  private:

    // Internal MSVCRT structure for file management
#ifdef WIN32
    ioinfo** __pioinfo;
#endif

    // Socket Descriptor
    struct SocketInfo
    {
      char Host[256];     // Default stdin/stdout descriptor: unused
      int  Port;          // Default stdin/stdout descriptor: unused

#ifdef WIN32
      SOCKET Sock;
#else
      int Sock;
#endif
      unsigned char Flag; // Linux: unused
    };

    map<string,CTcpFwd::SocketInfo*> Sockets; // List of active sockets

    // Initialization routine
    void Init();

  public:
    CTcpFwd();
    CTcpFwd(const char* Host, int Port);
    CTcpFwd(const char* SessionName, const char* Host, int Port);
    ~CTcpFwd();

    bool Connect(const char* SessionName, const char* Host, int Port);
    bool Disconnect(const char* SessionName);

    bool SwitchStdin(const char* SessionName);
    bool SwitchStdout(const char* SessionName);

    int print(const char* format, ...);
};



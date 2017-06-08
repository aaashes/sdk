#ifndef MEGACMDSHELLCOMMUNICATIONS_H
#define MEGACMDSHELLCOMMUNICATIONS_H

#include <string>
#include <iostream>

#include <mutex>

#include <sys/types.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <Shlwapi.h> //PathAppend
#else
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/un.h>
#endif
#define MEGACMDINITIALPORTNUMBER 12300


#ifdef _WIN32
#include <windows.h>
#define ERRNO WSAGetLastError()
#else
#define ERRNO errno
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#ifdef __MACH__
#define MSG_NOSIGNAL 0
#elif _WIN32
#define MSG_NOSIGNAL 0
#endif


class MegaCmdShellCommunications
{
public:
    MegaCmdShellCommunications();
    ~MegaCmdShellCommunications();

    int executeCommand(std::string command, std::ostream &output = std::cout); //TODO: COUT?? (wcout for windows)

    static int registerForStateChanges();

    void setResponseConfirmation(bool confirmation);

    static bool serverinitiatedfromshell;

private:
    static bool socketValid(int socket);
    static void closeSocket(int socket);
    static int listenToStateChanges(int receiveSocket);

    static bool confirmResponse;

#ifdef _WIN32
static int createSocket(int number = 0, bool net = true);
#else
static int createSocket(int number = 0, bool net = false);
#endif


};

#endif // MEGACMDSHELLCOMMUNICATIONS_H
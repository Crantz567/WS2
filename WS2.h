#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

class WS2
{
private:

	SOCKET sock;
	sockaddr_in sockStruct;
	int port;
	const char* ip;
	
	bool initialize();
	bool socketStructSetup();	
        bool createSocket();

public:

	WS2(int portNumber, const char* ipAddress);
	bool connectToServer();

};


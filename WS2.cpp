#include <iostream>
#include "WS2.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

WS2::WS2(int portNumber, const char* ipAddress)
{
	sock = INVALID_SOCKET;
	sockStruct = {};
	port = portNumber;
	ip = ipAddress;
}

bool WS2::initialize()
{
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int status = WSAStartup(ver, &data);
	
	if (status != 0)
	{
		return false;
	}
	
	return true;
}

bool WS2::socketStructSetup()
{
	if (port < 0 || port > 65535) // Check if valid port
	{
		return false;
	}
	
	sockStruct.sin_family = AF_INET;
	sockStruct.sin_port = htons(port); // host to network short
	int status = inet_pton(AF_INET, ip, &sockStruct.sin_addr);
	
	if (status != 1)
	{
		return false;
	}

	return true;
}

bool WS2::createSocket()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);	
	
	if (sock == INVALID_SOCKET)
	{
		return false;
	}

	return true;
}

bool WS2::connectToServer() // Calls all the necessary functions which are required to start a connection.
{
	if (!initialize())
	{
		std::cout << "Failed to start WSA\n";
		return false;
	}

	if (!socketStructSetup())
	{
		std::cout << "Failed to setup the sockaddr_in struct\n";
		WSACleanup();
		return false;
	}
	
	if (!createSocket())
	{
		std::cout << "Socket creation failed\n";
		WSACleanup();
		return false;
	}

	int status = connect(sock, (sockaddr*)&sockStruct, sizeof(sockStruct));
	if (status == SOCKET_ERROR)
	{
		std::cout << "Failed to connect\n" << WSAGetLastError();
		closesocket(sock);
		WSACleanup();
		return false;
	}
	
	std::cout << "Connected\n";
	return true;
}


#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

enum Packet
{
	P_ChatMessage,
	P_Test,
	P_Id,
	P_Vector2f
};

class Server
{
public:
	Server(int PORT, bool BroadcastPublically = false);
	bool ListenForNewConnection();

	void ReadyToPlay();
	void ChooseChaser();

private:
	bool sendall(int ID, char * data, int totalbytes);
	bool recvall(int ID, char * data, int totalbytes);

	bool SendInt(int ID, int _int);
	bool SendId(int ID);
	bool GetInt(int ID, int & _int);

	bool SendPacketType(int ID, Packet _packettype);
	bool GetPacketType(int ID, Packet & _packettype);

	bool SendString(int ID, std::string & _string);
	bool SendVector(int ID, sf::Vector2f position, int IDTwo);
	bool GetVector(int ID, sf::Vector2f& position, int& IDTwo);
	bool GetString(int ID, std::string & _string);

	bool ProcessPacket(int ID, Packet _packettype);

	std::vector<std::string> splitString(std::string string);

	static void ClientHandlerThread(int ID);

private:
	SOCKET Connections[100];
	int TotalConnections = 0;
	bool gameReady = false;

	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr);
	SOCKET sListen;


};

static Server * serverptr; //Serverptr is necessary so the static ClientHandler method can access the server instance/functions.

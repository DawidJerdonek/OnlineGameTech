#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> //For std::cout, std::endl, std::cin.getline
#include <SFML/Graphics.hpp>

enum Packet
{
	P_ChatMessage,
	P_Test,
	P_Id,
	P_Vector2f
};

class Client
{
public: //Public functions
	Client(std::string IP, int PORT);
	bool Connect();
	int m_playerId = 0;

	bool readyToPlay = false;
	int chaserNum = 0;

	sf::Vector2f playerPosGreen;
	sf::Vector2f playerPosBlue;
	sf::Vector2f playerPosYellow;

	bool SendString(std::string & _string);
	bool CloseConnection();
	bool SendVector(int _ID, sf::Vector2f _position);
	bool GetVector(int& ID, sf::Vector2f& position);

private: //Private functions
	bool ProcessPacket(Packet _packettype);
	static void ClientThread();
	//Sending Funcs
	bool sendall(char * data, int totalbytes);
	bool SendInt(int _int);
	bool SendPacketType(Packet _packettype);

	//Getting Funcs
	bool recvall(char * data, int totalbytes);
	bool GetInt(int & _int);
	bool GetPacketType(Packet & _packettype);
	bool GetString(std::string & _string);


	std::vector<std::string> splitString(std::string string);

private:
	SOCKET Connection;//This client's connection to the server
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function

};

static Client * clientptr; //This client ptr is necessary so that the ClientThread method can access the Client instance/methods. Since the ClientThread method is static, this is the simplest workaround I could think of since there will only be one instance of the client.
#pragma once
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <WS2tcpip.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

class Device
{
public:
	Device();
	void sendFromClientSocket();
	~Device();

	//Ipadress of the Socketserver
	string ipAddress = "192.168.1.71";
	//Listening port of the server
	int port = 54000;
	string deviceId, deviceType, deviceCategory, unit;
	int value;

	string generateDeviceId();
	string generateIpAdress();
	string generateDeviceType();
	string generateDeviceCategory();
	string generateUnit();
	string generateValue();
	void sendDevice(SOCKET clientSocket);
	void listenToServer(int sendResult, SOCKET clientSock);
};
#include "deviceinfo.h"


string Device::generateDeviceId() {

	deviceId = "agvr6854-g3545";

	return deviceId;
}
string Device::generateIpAdress(){
	string iPAdress = "192.168.1.10";
	
	return iPAdress;
}
string Device::generateDeviceType(){
	deviceType = "Sensor";
	return deviceType;
}
string Device::generateDeviceCategory(){
	deviceCategory = "Temperature";
	return deviceCategory;
}
string Device::generateUnit(){
	unit = "C";
	return unit;
}
string Device::generateValue(){
	srand((unsigned)time(0));
	
		
	string strValue = to_string((rand() % 40) + 1);
		return strValue;
	
}
void Device::sendFromClientSocket() {
	//Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	//Create clientsocket
	int wsok = WSAStartup(ver, &wsData);
	
	if (wsok != 0)
	{
		cout << "Can't initialize winsock! Error # " << wsok << endl;
		return;
	}

	//Create Socket
	SOCKET clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSock == INVALID_SOCKET)
	{
		cout << "Can't create a socket! Error # " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	//Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	
	//Connect to server
	int connResult = connect(clientSock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cout << "Can't connect to server, ERR # " << WSAGetLastError() << endl;
		closesocket(clientSock);
		WSACleanup();
	}
	sendDevice(clientSock);
	//Close down everything
	closesocket(clientSock);
	WSACleanup();
}
void Device::listenToServer(int sendResult, SOCKET clientSock) {

	char buf[4096];
	//This works because recv listens for incoming bytes.
	
					if (sendResult != SOCKET_ERROR)
					{
						//Wait for response
						ZeroMemory(buf, 4096);
						int bytesRecieved = recv(clientSock, buf, 4096, 0);
						if (bytesRecieved > 0)
						{
						//Echo response to console
							std::cout << "SERVER> " << std::string(buf, 0, bytesRecieved) << std::endl;
						}
					}
					else {
						std::cout << "Failed to send due to: Error " << WSAGetLastError() << std::endl;
					}

}
void Device::sendDevice(SOCKET clientSocket) {

	SOCKET clientSock = clientSocket;
	char c = ',';
	do
	{
		string query = generateDeviceId() + c + generateIpAdress() + c + generateDeviceType() + c + generateDeviceCategory() + c + generateValue() + c + generateUnit();
		int sendResult = send(clientSock, query.c_str(), query.size() + 1, 0);
		cout << query << endl;
		this_thread::sleep_for(chrono::milliseconds(10000));
	} while (true);
	


}
Device::Device()
{
}
Device::~Device()
{
}
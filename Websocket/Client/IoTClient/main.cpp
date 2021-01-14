#include "deviceinfo.h"

void main() {
	//Send precoded values from a websocket client to a websocket server 
	Device* myDevice = new Device;
	myDevice->sendFromClientSocket();
	delete myDevice;
}
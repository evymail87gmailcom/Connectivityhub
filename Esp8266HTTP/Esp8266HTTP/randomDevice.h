#pragma once
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

class Device
{
public:
	Device();
	//wifi-credentials
	const char* ssid = "INSERT_SSID_HERE";
	const char* password = "SSID_PASSWORD_HERE";
	//Your Domain name with URL path or IP address with path
	const char* serverName = "PATH_TO_HTTP_ENDPOINT";

	void startWifi();
	String getDevice();
	void sendDeviceThroughHTTP();
	~Device();



};


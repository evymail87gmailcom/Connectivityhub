#include "randomDevice.h"



void Device::startWifi() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    // Port defaults to 8266
    // ArduinoOTA.setPort(8266);

    // Hostname defaults to esp8266-[ChipID]
     ArduinoOTA.setHostname("ljhfbgkdn-5874");

    // No authentication by default
    // ArduinoOTA.setPassword((const char *)"123");

    ArduinoOTA.onStart([]() {
        Serial.println("Start");
        });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
        });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
        });
    ArduinoOTA.begin();
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

};

String Device::getDevice() {
    String deviceId, ipAdress, deviceType, deviceCategory, unit, protocol, dateTime;
    deviceId = "ljhfbgkdn-5874";
    ipAdress = WiFi.localIP().toString();
    deviceType = "Sensor";
    deviceCategory = "Temperature";
    unit = "C";
    protocol = "HTTP";

    int temp = random(0, 30);
    String value = String(temp);
    

    String msg = "{\"device_id\":\"" + deviceId + "\",\"ip_adress\":\"" + ipAdress + "\",\"protocol\":\"" + protocol + "\",\"device_type\":\"" + deviceType + "\",\"device_category\":\"" + deviceCategory + "\",\"value\":\"" + value + "\",\"unit\":\"" + unit + "\"}";
   
    return msg;
    
};

void Device::sendDeviceThroughHTTP() {

    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // Your Domain name with URL path or IP address with path
        http.begin(serverName);

        // Specify content-type header
        http.addHeader("Content-Type", "application/json");
        // Send HTTP POST request
        int httpResponseCode = http.POST(getDevice());
       
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        // Free resources
        http.end();
    }
    else {
        Serial.println("WiFi Disconnected");
    }
};




Device::Device()
{
}

Device::~Device()
{
}
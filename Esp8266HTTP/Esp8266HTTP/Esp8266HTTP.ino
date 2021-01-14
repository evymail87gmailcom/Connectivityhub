
#include "randomDevice.h"

//Timed event to control when the output is given
unsigned long lastTime = 0;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 15000;
Device* testDev = new Device;
void setup() {
    testDev->startWifi();

}



void loop() {
    //Sends this code without having to attach the arduino to a computer
    ArduinoOTA.handle();
    //Send an HTTP POST request every 10 minutes
    if ((millis() - lastTime) > timerDelay) {
       
        testDev->sendDeviceThroughHTTP();
       
        lastTime = millis();
    }

}
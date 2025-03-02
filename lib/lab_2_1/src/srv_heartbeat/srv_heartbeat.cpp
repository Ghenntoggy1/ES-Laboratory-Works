#include "srv_heartbeat.h"
#include <dd_led/dd_led.h>
#include <Arduino.h>

Led heartbeatLed(HEARTBEAT_PIN);

void srvHeartbeatSetup() {
    
}

void srvHeartbeatLoop() {
    heartbeatLed.toggle();
    delay(500);
}

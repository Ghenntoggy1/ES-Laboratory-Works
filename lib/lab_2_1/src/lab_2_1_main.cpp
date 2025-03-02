#include "lab_2_1_main.h"
#include "srv_serial_stdio/srv_serial_stdio.h"
#include "srv_heartbeat/srv_heartbeat.h"
#include <Arduino.h>

void lab_2_1_setup() {
    srvSerialSetup();
    printf("Serial communication initialized!\n");

    srvHeartbeatSetup();
    printf("Heartbeat initialized!\n");
}

void lab_2_1_loop() {
    // TODO: Implement
    srvHeartbeatLoop();
}
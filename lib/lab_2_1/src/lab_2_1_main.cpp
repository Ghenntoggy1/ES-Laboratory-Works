#include "lab_2_1_main.h"
#include "srv_serial_stdio/srv_serial_stdio.h"
#include "dd_led/dd_led.h"
#include <Arduino.h>

Led heartbeatLed(9);

void lab_2_1_setup() {
    srvSerialSetup();
    printf("Serial communication initialized!\n");
}

void lab_2_1_loop() {
    // TODO: Implement
}
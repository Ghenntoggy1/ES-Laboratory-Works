#include <Arduino.h>
#include "lab_0_main.h"
#include "dd_led/dd_led.h"
#include "dd_button/dd_button.h"

void lab_0_setup() {
    ledSetup();
    buttonSetup();
}

void lab_0_loop() {
    if (isButtonPressed()) {
        ledOn();
    } else {
        ledOff();
    }
}
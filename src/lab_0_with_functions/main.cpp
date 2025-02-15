#include <Arduino.h>
#include "main.h"
#include "dd_led/dd_led.h"
#include "dd_button/dd_button.h"

void setup() {
    ledSetup();
    buttonSetup();
}

void loop() {
    if (isButtonPressed()) {
        ledOn();
    } else {
        ledOff();
    }
}
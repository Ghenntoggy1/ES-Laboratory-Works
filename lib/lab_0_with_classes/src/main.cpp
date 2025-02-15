#include <Arduino.h>
#include "main.h"
#include "src/dd_led/dd_led.h"
#include "src/dd_button/dd_button.h"

Led led(13);
Button button(12);

void setup() {
    
}

void loop() {
    if (button.isPressed()) {
        led.on();
    } else {
        led.off();
    }
}
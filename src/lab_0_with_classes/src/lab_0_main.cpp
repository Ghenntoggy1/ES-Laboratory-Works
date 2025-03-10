#include <Arduino.h>
#include "lab_0_main.h"
#include "dd_led.h"
#include "dd_button.h"

Led led(13);
Button button(12);

void lab_0_setup() {
    
}

void lab_0_loop() {
    if (button.isPressed()) {
        led.on();
    } else {
        led.off();
    }
}
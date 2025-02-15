#include "dd_button.h"
#include <Arduino.h>

void buttonSetup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

int isButtonPressed() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        return 1;
    } else {
        return 0;
    }
}
#include "dd_button.h"
#include <Arduino.h>

Button::Button(int buttonPin): buttonPin(buttonPin) {
    pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor
}

int Button::readInput() {
    return digitalRead(buttonPin) ? 0 : 1;
}
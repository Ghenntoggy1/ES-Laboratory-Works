#include "dd_button.h"
#include <Arduino.h>

Button::Button(int buttonPin): buttonPin(buttonPin) {
    pinMode(buttonPin, INPUT_PULLUP);
}

bool Button::isPressed() {
    return digitalRead(buttonPin) == LOW;
}
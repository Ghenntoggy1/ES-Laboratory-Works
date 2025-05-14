#include "dd_button.h"

Button::Button(int buttonPin) {
    this->buttonPin = buttonPin;
    this->lastState = HIGH;
    this->lastDebounceTime = 0;
    this->lastReading = HIGH;
    pinMode(buttonPin, INPUT_PULLUP);
}

bool Button::isPressed() {
    bool reading = digitalRead(buttonPin);
    bool buttonPressed = false;

    if (reading != lastReading) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        if (reading != lastState) {
            lastState = reading;
            if (reading == LOW) {
                buttonPressed = true;
            }
        }
    }

    lastReading = reading;
    return buttonPressed;
}
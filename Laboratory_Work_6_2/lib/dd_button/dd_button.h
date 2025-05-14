#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define DEBOUNCE_DELAY 50

class Button {
private:
    int buttonPin;
    bool lastState;
    bool lastReading;
    unsigned long lastDebounceTime;

public:
    Button(int buttonPin);
    bool isPressed();
};

#endif
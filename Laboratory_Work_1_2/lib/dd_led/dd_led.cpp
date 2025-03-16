#include "dd_led.h"
#include <Arduino.h>

Led::Led(int ledPin): ledPin(ledPin) {
    pinMode(ledPin, OUTPUT);
}

void Led::on() {
    return digitalWrite(ledPin, HIGH);
}

void Led::off() {
    return digitalWrite(ledPin, LOW);
}

int Led::getState() {
    return digitalRead(ledPin);
}

void Led::toggle() {
    return digitalWrite(ledPin, getState() == HIGH ? LOW : HIGH);
}
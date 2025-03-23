#include "dd_potentiometer.h"
#include <Arduino.h>

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

int Potentiometer::getPotValue() {
    potValue = analogRead(pin);
    return potValue;
}
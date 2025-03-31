#include "dd_relay.h"
#include <Arduino.h>

Relay::Relay(int pin) {
    relayPin = pin;
    state = false;
}

void Relay::init() {
    pinMode(relayPin, OUTPUT);
    off();
}

void Relay::on() {
    digitalWrite(relayPin, HIGH);
    state = true;
}

void Relay::off() {
    digitalWrite(relayPin, LOW);
    state = false;
}

bool Relay::isOn() {
    return state;
}
#include "dd_led.h"
#include <Arduino.h>

void ledSetup() {
    pinMode(LED_PIN, OUTPUT);
}

void ledOn() {
    digitalWrite(LED_PIN, HIGH);
}

void ledOff() {
    digitalWrite(LED_PIN, LOW);
}
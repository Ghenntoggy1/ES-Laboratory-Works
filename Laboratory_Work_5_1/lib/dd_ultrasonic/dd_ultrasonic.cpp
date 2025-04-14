#include "dd_ultrasonic.h"
#include "Arduino.h"

DD_ULTRASONIC::DD_ULTRASONIC(int trg_pin, int echo_pin) {
    this->trg_pin = trg_pin;
    this->echo_pin = echo_pin;
    this->distance = 0.0;
    this->hysteresisBand = 5.0;
    this->targetSetpoint = 5.0;
}

void DD_ULTRASONIC::init() {
    pinMode(trg_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
}

float DD_ULTRASONIC::getDistance() {
    digitalWrite(trg_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trg_pin, LOW);
    delayMicroseconds(10);
    
    // by datasheet, use formula distance_cm = duration_uS / 58.0
    // pulseIn gives duration of the pulse in microseconds
    float duration = pulseIn(echo_pin, HIGH);
    distance = duration / 58.0;
    return distance;
}

float DD_ULTRASONIC::getHysteresisBand() {
    return hysteresisBand;
}

float DD_ULTRASONIC::getSetpoint() {
    return targetSetpoint;
}

void DD_ULTRASONIC::setHysteresisBand(float hysteresisBand) {
    this->hysteresisBand = hysteresisBand;
}

void DD_ULTRASONIC::setTargetSetpoint(float targetSetpoint) {
    this->targetSetpoint = targetSetpoint;
}
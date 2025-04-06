#include "dd_l298.h"
#include "Arduino.h"

DD_L298::DD_L298(int channelAEnPin, int channelAIn1Pin, int channelAIn2Pin,
                 int channelBEnPin, int channelBIn3Pin, int channelBIn4Pin) {
    this->channelAEnPin = channelAEnPin;
    this->channelAIn1Pin = channelAIn1Pin;
    this->channelAIn2Pin = channelAIn2Pin;

    this->channelBEnPin = channelBEnPin;
    this->channelBIn3Pin = channelBIn3Pin;
    this->channelBIn4Pin = channelBIn4Pin;
}

void DD_L298::init() {
    pinMode(channelAEnPin, OUTPUT);
    pinMode(channelAIn1Pin, OUTPUT);
    pinMode(channelAIn2Pin, OUTPUT);

    pinMode(channelBEnPin, OUTPUT);
    pinMode(channelBIn3Pin, OUTPUT);
    pinMode(channelBIn4Pin, OUTPUT);
}

int DD_L298::saturate(int value, int min, int max) {
    return constrain(value, min, max);
}

void DD_L298::set_pwm_motor_a(int speed) {
    if (speed < 0) {
        speed = saturate(speed, -255, 0);
    }
    else {
        speed = saturate(speed, 0, 255);
    }
    if (speed < 0) {
        digitalWrite(channelAIn1Pin, HIGH);
        digitalWrite(channelAIn2Pin, LOW);
    } else {
        digitalWrite(channelAIn1Pin, LOW);
        digitalWrite(channelAIn2Pin, HIGH);
    }
    
    analogWrite(channelAEnPin, abs(speed));
}

void DD_L298::set_pwm_motor_b(int speed) {
    if (speed < 0) {
        speed = saturate(speed, -255, 0);
    }
    else {
        speed = saturate(speed, 0, 255);
    }

    if (speed < 0) {
        digitalWrite(channelBIn3Pin, HIGH);
        digitalWrite(channelBIn4Pin, LOW);
    } else {
        digitalWrite(channelBIn3Pin, LOW);
        digitalWrite(channelBIn4Pin, HIGH);
    }

    analogWrite(channelBEnPin, abs(speed));
}

void DD_L298::stop_motor_a() {
    digitalWrite(channelAIn1Pin, LOW);
    digitalWrite(channelAIn2Pin, LOW);
    analogWrite(channelAEnPin, 0);
}

void DD_L298::stop_motor_b() {
    digitalWrite(channelBIn3Pin, LOW);
    digitalWrite(channelBIn4Pin, LOW);
    analogWrite(channelBEnPin, 0);
}

void DD_L298::stop_all_motors() {
    stop_motor_a();
    stop_motor_b();
}
#include "dd_dc_motor.h"
#include "dd_l298.h"
#include <Arduino.h>

DCMotor::DCMotor(DD_L298 *motorDriver, MotorChannel channel) {
    this->motorDriver = motorDriver;
    this->channel = channel;
    this->motorPower = 0;
    this->motorDirection = STOPPED;
}

void DCMotor::init() {
    motorDriver->init();
    stop_motor();
}

int DCMotor::saturate(int value, int min, int max) {
    return constrain(value, min, max);
}

void DCMotor::set_power(int power) {
    power = saturate(power, -100, 100);
    int powerVoltage = map(power, -100, 100, -255, 255);
    motorPower = power;
    motorDirection = (power > 0) ? FORWARD : (power < 0) ? BACKWARD : STOPPED;

    if (channel == MOTOR_A) {
        motorDriver->set_pwm_motor_a(powerVoltage);
    } else {
        motorDriver->set_pwm_motor_b(powerVoltage);
    }
}

void DCMotor::stop_motor() {
    if (channel == MOTOR_A) {
        motorDriver->stop_motor_a();
    } else {
        motorDriver->stop_motor_b();
    }
    motorPower = 0;
    motorDirection = STOPPED;
}

int DCMotor::get_power() {
    return motorPower;
}

String DCMotor::convertEnumNameToString(MotorDirection direction) {
    switch (direction) {
        case FORWARD:
            return "FORWARD";
        case BACKWARD:
            return "BACKWARD";
        case STOPPED:
            return "STOPPED";
        default:
            return "UNKNOWN";
    }
}

String DCMotor::is_going_forward() {
    if (motorPower > 0) {
        return convertEnumNameToString(FORWARD);
    } else if (motorPower < 0) {
        return convertEnumNameToString(BACKWARD);
    } else {
        return convertEnumNameToString(STOPPED);
    }
}
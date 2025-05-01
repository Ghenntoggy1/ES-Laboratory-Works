#include "dd_servo_motor.h"
#include "srv_global_vars.h"

ServoMotor::ServoMotor(int servoPin, int feedbackPin) {
    this->servoPin = servoPin;
    this->feedbackPin = feedbackPin;
    this->servo.attach(servoPin);
}

void ServoMotor::init() {
    pinMode(feedbackPin, INPUT);
    position = 0;
    feedbackValue = 0;
    setpoint = globalVariables.setpoint;
    input = 0;
    output = 0;
    kp = K_P; // Proportional gain
    ki = K_I; // Integral gain
    kd = K_D; // Derivative gain
    servo.write(0);
}

int ServoMotor::readFeedback() {
    int rawFeedbackValue = analogRead(feedbackPin);
    feedbackValue = map(rawFeedbackValue, 50, 600, 0, 180);
    return feedbackValue;
}

void ServoMotor::setPosition(int position) {
    this->position = position;
    servo.write(position);
}

int ServoMotor::getPosition() {
    return position;
}

float ServoMotor::getSetpoint() {
    return setpoint;
}

void ServoMotor::setSetpoint(float setpoint) {
    this->setpoint = setpoint;
}

float ServoMotor::getIntegral() {
    return integral;
}

void ServoMotor::setIntegral(float integral) {
    this->integral = integral;
}

float ServoMotor::getPrevError() {
    return prevError;
}

void ServoMotor::setPrevError(float prevError) {
    this->prevError = prevError;
}

void ServoMotor::setOutput(float output) {
    this->output = output;
}

float ServoMotor::getOutput() {
    return output;
}

float ServoMotor::getKp() {
    return kp;
}

float ServoMotor::getKi() {
    return ki;
}

float ServoMotor::getKd() {
    return kd;
}

int ServoMotor::getFeedback() {
    return feedbackValue;
}
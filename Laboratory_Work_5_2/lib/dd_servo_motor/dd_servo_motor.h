#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Arduino.h>
#include <Servo.h>
#include <Arduino_FreeRTOS.h>

#define K_P 0.3 // Proportional gain
#define K_I 0.5 // Integral gain
#define K_D 0.2 // Derivative gain

class ServoMotor {
private:
    int servoPin;
    int feedbackPin;
    Servo servo;
    int position;
    int feedbackValue;

    float setpoint;
    float input;
    float output;
    float kp; 
    float ki; 
    float kd;
    float prevError;
    float integral;

public:
    ServoMotor(int servoPin, int feedbackPin);
    void init();
    int readFeedback();
    void setPosition(int position);
    int getPosition();
    float getSetpoint();
    void setSetpoint(float setpoint);
    float getIntegral();
    void setIntegral(float integral);
    float getPrevError();
    void setPrevError(float prevError);
    void setOutput(float output);
    float getOutput();
    float getKp();
    float getKi();
    float getKd();
    int getFeedback();
};

#endif
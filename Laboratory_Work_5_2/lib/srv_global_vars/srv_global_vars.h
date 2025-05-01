#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include "dd_servo_motor.h"

#define SERVO_PIN 9
#define FEEDBACK_PIN A3

#define SETPOINT_DEFAULT 90.0

struct GlobalVariables {
    ServoMotor *servoMotor;
    float setpoint;

    SemaphoreHandle_t serialMutex;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

ServoMotor *getServoMotor();

float getSetpoint();

SemaphoreHandle_t getSerialMutex();

#endif
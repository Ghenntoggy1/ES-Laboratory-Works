#include "srv_global_vars.h"
#include <stdio.h>

GlobalVariables globalVariables = {
    .servoMotor = NULL,
    .setpoint = 0.0,
    .serialMutex = NULL,
};

void globalVariablesSetup()
{
    globalVariables.servoMotor = new ServoMotor(SERVO_PIN, FEEDBACK_PIN);
    globalVariables.setpoint = SETPOINT_DEFAULT;
    globalVariables.servoMotor->init();

    globalVariables.serialMutex = xSemaphoreCreateMutex();
}

ServoMotor *getServoMotor()
{
    return globalVariables.servoMotor;
}

float getSetpoint()
{
    return globalVariables.setpoint;
}

SemaphoreHandle_t getSerialMutex()
{
    return globalVariables.serialMutex;
}
#include "srv_global_vars.h"
#include <stdio.h>
#include <Arduino.h>

GlobalVariables globalVariables = {
    .motorA = NULL,
    .motorDriver = NULL,
    .serialMutex = NULL,
};

void globalVariablesSetup()
{
    globalVariables.motorDriver = new DD_L298(DD_L298_CHANNEL_ENA_PIN, DD_L298_CHANNEL_IN1_PIN, DD_L298_CHANNEL_IN2_PIN);
    globalVariables.motorA = new DCMotor(globalVariables.motorDriver, MOTOR_A);
    globalVariables.serialMutex = xSemaphoreCreateMutex();
}

DCMotor *getMotorA()
{
    return globalVariables.motorA;
}

SemaphoreHandle_t getSerialMutex()
{
    return globalVariables.serialMutex;
}
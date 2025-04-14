#include "srv_global_vars.h"
#include <stdio.h>
#include <Arduino.h>

GlobalVariables globalVariables = {
    .motorA = NULL,
    .motorDriver = NULL,
    .ultrasonicSensor = NULL,
    .ledHystLow = NULL,
    .ledHystHigh = NULL,
    .serialMutex = NULL,
};

void globalVariablesSetup()
{
    globalVariables.ledHystLow = new Led(DD_LED_HYST_LOW_PIN);
    globalVariables.ledHystHigh = new Led(DD_LED_HYST_HIGH_PIN);

    globalVariables.motorDriver = new DD_L298(DD_L298_CHANNEL_ENA_PIN, DD_L298_CHANNEL_IN1_PIN, DD_L298_CHANNEL_IN2_PIN);
    
    globalVariables.motorA = new DCMotor(globalVariables.motorDriver, MOTOR_A);
    globalVariables.motorA->init();

    globalVariables.ultrasonicSensor = new DD_ULTRASONIC(DD_ULTRASONIC_TRIG_PIN, DD_ULTRASONIC_ECHO_PIN);
    globalVariables.ultrasonicSensor->init();

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
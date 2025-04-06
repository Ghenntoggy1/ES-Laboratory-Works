#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include "dd_dc_motor.h"
#include "dd_l298.h"

#define DD_L298_CHANNEL_ENA_PIN 8
#define DD_L298_CHANNEL_IN1_PIN 2
#define DD_L298_CHANNEL_IN2_PIN 3

#define DD_L298_CHANNEL_ENB_PIN 9
#define DD_L298_CHANNEL_IN3_PIN 4
#define DD_L298_CHANNEL_IN4_PIN 5

struct GlobalVariables {
    DCMotor *motorA;
    DD_L298 *motorDriver;

    SemaphoreHandle_t serialMutex;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

DCMotor *getMotorA();

SemaphoreHandle_t getSerialMutex();

#endif
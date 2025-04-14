#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include "dd_dc_motor.h"
#include "dd_l298.h"
#include "dd_ultrasonic.h"
#include "dd_led.h"

#define DD_LED_HYST_LOW_PIN 6
#define DD_LED_HYST_HIGH_PIN 7

#define DD_ULTRASONIC_TRIG_PIN 10
#define DD_ULTRASONIC_ECHO_PIN 11

#define DD_L298_CHANNEL_ENA_PIN 8
#define DD_L298_CHANNEL_IN1_PIN 2
#define DD_L298_CHANNEL_IN2_PIN 3

#define DD_L298_CHANNEL_ENB_PIN 9
#define DD_L298_CHANNEL_IN3_PIN 4
#define DD_L298_CHANNEL_IN4_PIN 5

struct GlobalVariables {
    DCMotor *motorA;
    DD_L298 *motorDriver;
    DD_ULTRASONIC *ultrasonicSensor;
    Led *ledHystLow;
    Led *ledHystHigh;

    SemaphoreHandle_t serialMutex;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

DCMotor *getMotorA();

SemaphoreHandle_t getSerialMutex();

#endif
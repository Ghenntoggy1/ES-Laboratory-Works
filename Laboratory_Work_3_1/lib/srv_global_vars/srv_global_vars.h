#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include "dd_joystick.h"
#include "dd_led.h"

#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1
#define JOYSTICK_BUTTON_PIN 2
#define LED_FORWARD_PIN 10
#define LED_BACKWARD_PIN 9
#define LED_RIGHT_PIN 11
#define LED_LEFT_PIN 12
#define THRESHOLD_X_STAND 25
#define THRESHOLD_Y_STAND 25
#define THRESHOLD_X_RUN 350
#define THRESHOLD_Y_RUN 350


struct GlobalVariables {
    Joystick *joystick;
    int globalJoystickXValue;
    int globalJoystickYValue;
    bool globalJoystickButtonState;
    Led *ledForward;
    Led *ledBackward;
    Led *ledRight;
    Led *ledLeft;
    SemaphoreHandle_t joystickMutex;
    SemaphoreHandle_t serialMutex;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

Joystick *getJoystick();
SemaphoreHandle_t getJoystickMutex();
SemaphoreHandle_t getSerialMutex();

#endif
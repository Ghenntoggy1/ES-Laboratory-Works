#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include "dd_joystick.h"
#include "dd_potentiometer.h"
#include "dd_led.h"


#define JOYSTICK_X_PIN A6
#define JOYSTICK_Y_PIN A7
#define POTENTIOMETER_PIN A0
#define JOYSTICK_BUTTON_PIN 2

#define LED_FORWARD_PIN 10
#define LED_BACKWARD_PIN 9
#define LED_RIGHT_PIN 11
#define LED_LEFT_PIN 12

#define THRESHOLD_X_STAND 25
#define THRESHOLD_Y_STAND 25
#define THRESHOLD_X_RUN 75
#define THRESHOLD_Y_RUN 75


struct GlobalVariables {
    Joystick *joystick;
    Potentiometer *potentiometer;
    int globalJoystickXValue;
    int globalJoystickYValue;
    int globalPotentiometerValue;

    int globalJoystickRawXValue;
    int globalJoystickRawYValue;
    int globalJoystickMilliVoltXValue;
    int globalJoystickMilliVoltYValue;
    int globalJoystickSatMilliVoltXValue;
    int globalJoystickSatMilliVoltYValue;
    int globalJoystickSaltPiperFilteredMilliVoltXValue;
    int globalJoystickSaltPiperFilteredMilliVoltYValue;
    int globalJoystickWeightedAverageFilteredMilliVoltXValue;
    int globalJoystickWeightedAverageFilteredMilliVoltYValue;
    int globalJoystickPhysicalXValue;
    int globalJoystickPhysicalYValue;

    int globalPotentiometerRawValue;
    int globalPotentiometerMilliVoltValue;
    int globalPotentiometerSatMilliVoltValue;
    int globalPotentiometerSaltPiperFilteredMilliVoltValue;
    int globalPotentiometerWeightedAverageFilteredMilliVoltValue;
    int globalPotentiometerPhysicalValue;

    bool globalJoystickButtonState;
    Led *ledForward;
    Led *ledBackward;
    Led *ledRight;
    Led *ledLeft;
    SemaphoreHandle_t joystickMutex;
    SemaphoreHandle_t potentiometerMutex;
    SemaphoreHandle_t serialMutex;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

Joystick *getJoystick();
Potentiometer *getPotentiometer();
SemaphoreHandle_t getJoystickMutex();
SemaphoreHandle_t getSerialMutex();

#endif
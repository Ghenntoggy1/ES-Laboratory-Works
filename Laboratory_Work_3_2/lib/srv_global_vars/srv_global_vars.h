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

#define LED_POTENTIOMETER_PIN 8

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
    Led *ledPotentiometer;
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
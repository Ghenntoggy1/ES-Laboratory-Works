#include "srv_global_vars.h"
#include <stdio.h>
#include <Arduino.h>

GlobalVariables globalVariables = {
    .joystick = nullptr,
    .potentiometer = nullptr,
    .globalJoystickXValue = 0,
    .globalJoystickYValue = 0,
    .globalJoystickButtonState = false,
    .ledForward = nullptr,
    .ledBackward = nullptr,
    .ledRight = nullptr,
    .ledLeft = nullptr,
    .joystickMutex = NULL,
    .serialMutex = NULL,
};

void globalVariablesSetup()
{
    globalVariables.joystick = new Joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN, JOYSTICK_BUTTON_PIN);
    globalVariables.potentiometer = new Potentiometer(POTENTIOMETER_PIN);
    globalVariables.ledForward = new Led(LED_FORWARD_PIN);
    globalVariables.ledBackward = new Led(LED_BACKWARD_PIN);
    globalVariables.ledRight = new Led(LED_RIGHT_PIN);
    globalVariables.ledLeft = new Led(LED_LEFT_PIN);
    globalVariables.joystickMutex = xSemaphoreCreateMutex();
    globalVariables.serialMutex = xSemaphoreCreateMutex();
}

Joystick *getJoystick(){
    return globalVariables.joystick;
}

Potentiometer *getPotentiometer()
{
    return globalVariables.potentiometer;
}

int getGlobalJoystickXValue()
{
    return globalVariables.globalJoystickXValue;
}

int getGlobalJoystickYValue()
{
    return globalVariables.globalJoystickYValue;
}

bool getGlobalJoystickButtonState()
{
    return globalVariables.globalJoystickButtonState;
}

int getGlobalPotValue()
{
    return globalVariables.potentiometer->getPotValue();
}

SemaphoreHandle_t getJoystickMutex()
{
    return globalVariables.joystickMutex;
}

SemaphoreHandle_t getSerialMutex()
{
    return globalVariables.serialMutex;
}
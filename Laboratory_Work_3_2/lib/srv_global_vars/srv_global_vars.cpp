#include "srv_global_vars.h"
#include <stdio.h>
#include <Arduino.h>

GlobalVariables globalVariables = {
    .joystick = nullptr,
    .potentiometer = nullptr,
    .globalJoystickXValue = 0,
    .globalJoystickYValue = 0,
    .globalPotentiometerValue = 0,

    .globalJoystickRawXValue = 0,
    .globalJoystickRawYValue = 0,
    .globalJoystickMilliVoltXValue = 0,
    .globalJoystickMilliVoltYValue = 0,
    .globalJoystickSatMilliVoltXValue = 0,
    .globalJoystickSatMilliVoltYValue = 0,
    .globalJoystickSaltPiperFilteredMilliVoltXValue = 0,
    .globalJoystickSaltPiperFilteredMilliVoltYValue = 0,
    .globalJoystickWeightedAverageFilteredMilliVoltXValue = 0,
    .globalJoystickWeightedAverageFilteredMilliVoltYValue = 0,
    .globalJoystickPhysicalXValue = 0,
    .globalJoystickPhysicalYValue = 0,

    .globalPotentiometerRawValue = 0,
    .globalPotentiometerMilliVoltValue = 0,
    .globalPotentiometerSatMilliVoltValue = 0,
    .globalPotentiometerSaltPiperFilteredMilliVoltValue = 0,
    .globalPotentiometerWeightedAverageFilteredMilliVoltValue = 0,
    .globalPotentiometerPhysicalValue = 0,

    .globalJoystickButtonState = false,
    .ledForward = nullptr,
    .ledBackward = nullptr,
    .ledRight = nullptr,
    .ledLeft = nullptr,
    .joystickMutex = NULL,
    .potentiometerMutex = NULL,
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
    globalVariables.potentiometerMutex = xSemaphoreCreateMutex();
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

int getGlobalPotentiometerValue()
{
    return globalVariables.globalPotentiometerValue;
}

int getGlobalJoystickRawXValue()
{
    return globalVariables.globalJoystickRawXValue;
}

int getGlobalJoystickRawYValue()
{
    return globalVariables.globalJoystickRawYValue;
}

int getGlobalJoystickMilliVoltXValue()
{
    return globalVariables.globalJoystickMilliVoltXValue;
}

int getGlobalJoystickMilliVoltYValue()
{
    return globalVariables.globalJoystickMilliVoltYValue;
}

int getGlobalJoystickSatMilliVoltXValue()
{
    return globalVariables.globalJoystickSatMilliVoltXValue;
}

int getGlobalJoystickSatMilliVoltYValue()
{
    return globalVariables.globalJoystickSatMilliVoltYValue;
}

int getGlobalJoystickSaltPiperFilteredMilliVoltXValue()
{
    return globalVariables.globalJoystickSaltPiperFilteredMilliVoltXValue;
}

int getGlobalJoystickSaltPiperFilteredMilliVoltYValue()
{
    return globalVariables.globalJoystickSaltPiperFilteredMilliVoltYValue;
}

int getGlobalJoystickWeightedAverageFilteredMilliVoltXValue()
{
    return globalVariables.globalJoystickWeightedAverageFilteredMilliVoltXValue;
}

int getGlobalJoystickWeightedAverageFilteredMilliVoltYValue()
{
    return globalVariables.globalJoystickWeightedAverageFilteredMilliVoltYValue;
}

int getGlobalJoystickPhysicalXValue()
{
    return globalVariables.globalJoystickPhysicalXValue;
}

int getGlobalJoystickPhysicalYValue()
{
    return globalVariables.globalJoystickPhysicalYValue;
}

int getGlobalPotentiometerRawValue()
{
    return globalVariables.globalPotentiometerRawValue;
}

int getGlobalPotentiometerMilliVoltValue()
{
    return globalVariables.globalPotentiometerMilliVoltValue;
}

int getGlobalPotentiometerSatMilliVoltValue()
{
    return globalVariables.globalPotentiometerSatMilliVoltValue;
}

int getGlobalPotentiometerSaltPiperFilteredMilliVoltValue()
{
    return globalVariables.globalPotentiometerSaltPiperFilteredMilliVoltValue;
}

int getGlobalPotentiometerWeightedAverageFilteredMilliVoltValue()
{
    return globalVariables.globalPotentiometerWeightedAverageFilteredMilliVoltValue;
}

int getGlobalPotentiometerPhysicalValue()
{
    return globalVariables.globalPotentiometerPhysicalValue;
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

SemaphoreHandle_t getPotentiometerMutex()
{
    return globalVariables.potentiometerMutex;
}

SemaphoreHandle_t getSerialMutex()
{
    return globalVariables.serialMutex;
}
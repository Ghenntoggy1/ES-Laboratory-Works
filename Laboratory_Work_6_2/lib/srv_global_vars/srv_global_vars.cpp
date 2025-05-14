#include "srv_global_vars.h"
#include "dd_button.h"
#include "dd_led.h"
#include <stdio.h>


GlobalVariables globalVariables = {
    .eastWestRedLed = nullptr,
    .eastWestYellowLed = nullptr,
    .eastWestGreenLed = nullptr,

    .northSouthRedLed = nullptr,
    .northSouthYellowLed = nullptr,
    .northSouthGreenLed = nullptr,

    .switchDirectionButton = nullptr,
    .nightModeButton = nullptr,

    .currentState = 0,
    .isNightModeActive = false,
    .isNightModeYellowOn = false,
    .northSouthRequest = false,

    .stateMutex = NULL,
};

void globalVariablesSetup()
{
    globalVariables.eastWestRedLed = new Led(EAST_WEST_RED_LED_PIN);
    globalVariables.eastWestYellowLed = new Led(EAST_WEST_YELLOW_LED_PIN);
    globalVariables.eastWestGreenLed = new Led(EAST_WEST_GREEN_LED_PIN);

    globalVariables.northSouthRedLed = new Led(NORTH_SOUTH_RED_LED_PIN);
    globalVariables.northSouthYellowLed = new Led(NORTH_SOUTH_YELLOW_LED_PIN);
    globalVariables.northSouthGreenLed = new Led(NORTH_SOUTH_GREEN_LED_PIN);

    globalVariables.switchDirectionButton = new Button(SWITCH_DIRECTION_BUTTON_PIN);
    globalVariables.nightModeButton = new Button(NIGHT_MODE_BUTTON_PIN);

    globalVariables.currentState = STATE_EAST_WEST_GREEN;

    globalVariables.stateMutex = xSemaphoreCreateMutex();
}

Led *getEastWestRedLed()
{
    return globalVariables.eastWestRedLed;
}

Led *getEastWestYellowLed()
{
    return globalVariables.eastWestYellowLed;
}

Led *getEastWestGreenLed()
{
    return globalVariables.eastWestGreenLed;
}

Led *getNorthSouthRedLed()
{
    return globalVariables.northSouthRedLed;
}

Led *getNorthSouthYellowLed()
{
    return globalVariables.northSouthYellowLed;
}

Led *getNorthSouthGreenLed()
{
    return globalVariables.northSouthGreenLed;
}

Button *getSwitchDirectionButton()
{
    return globalVariables.switchDirectionButton;
}

Button *getNightModeButton()
{
    return globalVariables.nightModeButton;
}

int getCurrentState()
{
    return globalVariables.currentState;
}

void setCurrentState(int state)
{
    globalVariables.currentState = state;
}

bool isNightModeActive()
{
    return globalVariables.isNightModeActive;
}

void setNightModeActive(bool active)
{
    globalVariables.isNightModeActive = active;
}

bool isNightModeYellowOn()
{
    return globalVariables.isNightModeYellowOn;
}

void setNightModeYellowOn(bool active)
{
    globalVariables.isNightModeYellowOn = active;
}

bool isNorthSouthRequested()
{
    return globalVariables.northSouthRequest;
}

void setNorthSouthRequest(bool requested)
{
    globalVariables.northSouthRequest = requested;
}

SemaphoreHandle_t getStateMutex()
{
    return globalVariables.stateMutex;
}
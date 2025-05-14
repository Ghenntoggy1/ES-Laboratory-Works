#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include "dd_button.h"
#include "dd_led.h"

#define STATE_EAST_WEST_GREEN 0
#define STATE_EAST_WEST_YELLOW 1
#define STATE_NORTH_SOUTH_ENTRY_YELLOW 2
#define STATE_NORTH_SOUTH_GREEN 3
#define STATE_NORTH_SOUTH_YELLOW 4
#define STATE_EAST_WEST_ENTRY_YELLOW 5

#define EAST_WEST_RED_LED_PIN 12
#define EAST_WEST_YELLOW_LED_PIN 11
#define EAST_WEST_GREEN_LED_PIN 10

#define NORTH_SOUTH_RED_LED_PIN 7
#define NORTH_SOUTH_YELLOW_LED_PIN 6
#define NORTH_SOUTH_GREEN_LED_PIN 5

#define SWITCH_DIRECTION_BUTTON_PIN 3
#define NIGHT_MODE_BUTTON_PIN 2

#define EAST_WEST_GREEN_TIME 5000
#define EAST_WEST_YELLOW_TIME 2000
#define NORTH_SOUTH_ENTRY_YELLOW_TIME 2000
#define NORTH_SOUTH_GREEN_TIME 5000
#define NORTH_SOUTH_YELLOW_TIME 2000
#define EAST_WEST_ENTRY_YELLOW_TIME 2000

#define NIGHT_MODE_BLINKING_TIME_REC 500

struct GlobalVariables {
    Led *eastWestRedLed;
    Led *eastWestYellowLed;
    Led *eastWestGreenLed;

    Led *northSouthRedLed;
    Led *northSouthYellowLed;
    Led *northSouthGreenLed;

    Button *switchDirectionButton;
    Button *nightModeButton;

    int currentState;
    bool isNightModeActive;
    bool isNightModeYellowOn;
    bool northSouthRequest;
    
    SemaphoreHandle_t stateMutex;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

Led *getEastWestRedLed();
Led *getEastWestYellowLed();
Led *getEastWestGreenLed();

Led *getNorthSouthRedLed();
Led *getNorthSouthYellowLed();
Led *getNorthSouthGreenLed();

Button *getSwitchDirectionButton();
Button *getNightModeButton();

int getCurrentState();
void setCurrentState(int state);

bool isNightModeActive();
void setNightModeActive(bool active);

bool isNightModeYellowOn();
void setNightModeYellowOn(bool active);

bool isNorthSouthRequested();
void setNorthSouthRequest(bool request);

SemaphoreHandle_t getStateMutex();

#endif
#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include <queue.h>
#include <semphr.h>
#include "dd_led.h"
#include "dd_button.h"

#define LED_PIN 8
#define BUTTON_PIN 9

#define BUTTON_LOW LOW
#define BUTTON_HIGH HIGH

#define LED_TIME_MS_OFF_TO_ON 10
#define LED_TIME_MS_ON_TO_OFF 10
#define LED_TIME_MS_BLINK 1000

#define LED_OFF_STATE 0
// #define LED_BLINK_STATE 1
#define LED_ON_STATE 1

struct State {
    unsigned long Out; // Led State
    unsigned long Time; // delay in ms units
    unsigned long Next[2];// next state for inputs
};

typedef const struct State STyp;

STyp FSM[3]= {
    {0, LED_TIME_MS_OFF_TO_ON, {LED_OFF_STATE, LED_ON_STATE}},
    // {1, LED_TIME_MS_BLINK, {LED_OFF_STATE, LED_ON_STATE}},
    {1, LED_TIME_MS_ON_TO_OFF, {LED_ON_STATE, LED_OFF_STATE}}
};
// int FSM_State = LED_OFF_STATE;

struct GlobalVariables {
    Led *led;
    Button *button;

    int FSM_State;
    int ledState;
    int buttonState;

    SemaphoreHandle_t serialMutex;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

Led *getLed();
Button *getButton();

int getFSMState();
void setFSMState(int state);
int getLedState();
int getButtonState();
void setLedState(int state);
void setButtonState(int state);

SemaphoreHandle_t getSerialMutex();

#endif
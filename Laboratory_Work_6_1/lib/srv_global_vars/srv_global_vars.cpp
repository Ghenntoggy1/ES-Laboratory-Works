#include "srv_global_vars.h"
#include <stdio.h>

GlobalVariables globalVariables = {
    .led = NULL,
    .button = NULL,
    .FSM_State = LED_OFF_STATE,
    .ledState = LED_OFF_STATE,
    .buttonState = 0,
    .serialMutex = NULL,
};

void globalVariablesSetup()
{
    globalVariables.led = new Led(LED_PIN);
    globalVariables.led->init();
    globalVariables.button = new Button(BUTTON_PIN);
    globalVariables.FSM_State = LED_OFF_STATE;
    globalVariables.buttonState = globalVariables.button->readInput();
    globalVariables.ledState = globalVariables.led->getState() ? LED_ON_STATE : LED_OFF_STATE;
    globalVariables.serialMutex = xSemaphoreCreateMutex();
}

Led *getLed()
{
    return globalVariables.led;
}

Button *getButton()
{
    return globalVariables.button;
}

int getFSMState()
{
    return globalVariables.FSM_State;
}

void setFSMState(int state)
{
    globalVariables.FSM_State = state;
}

int getLedState()
{
    return globalVariables.ledState;
}

int getButtonState()
{
    return globalVariables.buttonState;
}

void setLedState(int ledState)
{
    globalVariables.ledState = ledState;
}

void setButtonState(int buttonState)
{
    globalVariables.buttonState = buttonState;
}

SemaphoreHandle_t getSerialMutex()
{
    return globalVariables.serialMutex;
}
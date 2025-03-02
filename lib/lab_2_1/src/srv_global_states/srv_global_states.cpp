#include "srv_global_states.h"
#include <stdio.h>
#include <Arduino.h>

volatile GlobalVariables globalStates = {
    .led1State = LOW,
    .led2State = LOW,
    .counter = 0,
};

void globalStatesSetup()
{
    globalStates.led1State = LOW;
    globalStates.led2State = LOW;
    globalStates.counter = 5;
}

void setLed1State(bool state)
{
    globalStates.led1State = state;
}

void setLed2State(bool state)
{
    globalStates.led2State = state;
}

void setCounter(int value)
{
    globalStates.counter = value;
}

void incrementCounter()
{
    globalStates.counter++;
}

void decrementCounter()
{
    if (globalStates.counter > 0) {
        globalStates.counter--;
    }
}

bool getLed1State()
{
    return globalStates.led1State;
}

bool getLed2State()
{
    return globalStates.led2State;
}

int getCounter()
{
    return globalStates.counter;
}
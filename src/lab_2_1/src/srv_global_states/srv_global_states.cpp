#include "srv_global_states.h"
#include <stdio.h>
#include <Arduino.h>

volatile GlobalVariables_lab_2_1 globalStates = {
    .led1State = LOW,
    .led2State = LOW,
    .counter = 0,
};

void lab_2_1_globalStatesSetup()
{
    globalStates.led1State = LOW;
    globalStates.led2State = LOW;
    globalStates.counter = 5;
}

void lab_2_1_setLed1State(bool state)
{
    globalStates.led1State = state;
}

void lab_2_1_setLed2State(bool state)
{
    globalStates.led2State = state;
}

void lab_2_1_setCounter(int value)
{
    globalStates.counter = value;
}

bool lab_2_1_getLed1State()
{
    return globalStates.led1State;
}

bool lab_2_1_getLed2State()
{
    return globalStates.led2State;
}

int lab_2_1_getCounter()
{
    return globalStates.counter;
}
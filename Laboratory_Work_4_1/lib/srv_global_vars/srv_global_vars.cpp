#include "srv_global_vars.h"
#include <stdio.h>
#include <Arduino.h>

GlobalVariables globalVariables = {
    .relay = nullptr,
    .globalRelayState = 0,
    .serialMutex = NULL,
};

void globalVariablesSetup()
{
    globalVariables.relay = new Relay(RELAY_PIN);
    globalVariables.relay->init();
    globalVariables.serialMutex = xSemaphoreCreateMutex();
}

Relay *getRelay(){
    return globalVariables.relay;
}

int globalRelayState()
{
    return globalVariables.globalRelayState;
}

SemaphoreHandle_t getSerialMutex()
{
    return globalVariables.serialMutex;
}
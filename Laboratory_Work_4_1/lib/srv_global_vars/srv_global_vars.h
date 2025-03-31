#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include "dd_relay.h"


#define RELAY_PIN 8

struct GlobalVariables {
    Relay *relay;
    int globalRelayState;

    SemaphoreHandle_t serialMutex;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

Relay *getRelay();
SemaphoreHandle_t getSerialMutex();

#endif
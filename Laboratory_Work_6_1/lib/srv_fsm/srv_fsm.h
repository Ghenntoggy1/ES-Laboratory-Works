#ifndef SRV_FSM_H
#define SRV_FSM_H

#include "dd_button.h"
#include <Arduino.h>

typedef enum {
    STATE_OFF,
    STATE_BLINK,
    STATE_ON,
    STATE_COUNT,
} FSMState;

static const char* FSMStateStrings[] = {
    "STATE_OFF",
    "STATE_BLINK",
    "STATE_ON",
    "STATE_COUNT"
};

typedef enum {
    OFF_TO_BLINKING,
    BLINKING_TO_ON,
    ON_TO_OFF
} FSMTransition;

static const char* FSMTransitionStrings[] = {
    "OFF_TO_BLINKING",
    "BLINKING_TO_ON",
    "ON_TO_OFF"
};

struct StateTable {
    FSMState currentState;
    FSMState nextState;
    void (*onEnterAction)();
    void (*onDoAction)();
    void (*onExitAction)();
};
typedef const struct StateTable StateTableStruct;

extern StateTableStruct stateTable[STATE_COUNT];

void initFSM();
void runFSM();

#endif
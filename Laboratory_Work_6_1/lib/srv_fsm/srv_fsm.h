#ifndef SRV_FSM_H
#define SRV_FSM_H

#include "dd_button.h"
#include <Arduino.h>

#define FSM_TRANSITION_COUNT 4
#define FSM_STATE_COUNT 3

typedef enum {
    STATE_OFF,
    STATE_BLINK,
    STATE_ON,
    STATE_COUNT,
} FSMState;

static const char* FSMStateStrings[FSM_STATE_COUNT] = {
    "STATE_OFF",
    "STATE_BLINK",
    "STATE_ON"
};

typedef enum {
    OFF_TO_BLINKING,
    BLINKING_TO_ON,
    ON_TO_BLINKING,
    BLINKING_TO_OFF
} FSMTransition;

static const char* FSMTransitionStrings[FSM_TRANSITION_COUNT] = {
    "OFF_TO_BLINKING",
    "BLINKING_TO_ON",
    "ON_TO_BLINKING",
    "BLINKING_TO_OFF"
};

struct StateTable {
    FSMState currentState;
    FSMState nextState;
    void (*onEnterAction)();
    void (*onDoAction)();
    void (*onExitAction)();
};
typedef const struct StateTable StateTableStruct;

extern StateTableStruct stateTable[FSM_TRANSITION_COUNT];

void initFSM();
void runFSM();

#endif
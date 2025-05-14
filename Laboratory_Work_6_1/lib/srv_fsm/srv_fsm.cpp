#include "srv_fsm.h"
#include "srv_global_vars.h"
#include <Arduino.h>

FSMState currentState;
FSMTransition currentTransition;

void onEntryStateOff() {
    printf("Current State: %s\n", FSMStateStrings[currentState]);
    getLed()->off();
}

void onDoStateOff() { }

void onExitStateOff() {
    printf("Transition %s\n", FSMTransitionStrings[currentTransition]);
    printf("Exiting State: %s\n", FSMStateStrings[currentState]);
}

void onEntryStateBlink() {
    printf("Current State: %s\n", FSMStateStrings[currentState]);
}

void onDoStateBlinking() {
    static unsigned long lastBlinkTime = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - lastBlinkTime >= (currentTransition == BLINKING_TO_ON ? OFF_TO_BLINKING_TIME_MS : ON_TO_BLINKING_TIME_MS)) {
        getLed()->toggle();
        lastBlinkTime = currentMillis;
    }
}

void onExitStateBlink() {
    printf("Transition %s\n", FSMTransitionStrings[currentTransition]);
    printf("Exiting State: %s\n", FSMStateStrings[currentState]);
}

void onEntryStateOn() {
    printf("Current State: %s\n", FSMStateStrings[currentState]);
    getLed()->on();
}

void onDoStateOn() { }

void onExitStateOn() {
    printf("Transition %s\n", FSMTransitionStrings[currentTransition]);
    printf("Exiting State: %s\n", FSMStateStrings[currentState]);
}

StateTableStruct stateTable[FSM_TRANSITION_COUNT] = {
    [OFF_TO_BLINKING] = { STATE_OFF, STATE_BLINK, onEntryStateOff, onDoStateOff, onExitStateOff },
    [BLINKING_TO_ON] = { STATE_BLINK, STATE_ON, onEntryStateBlink, onDoStateBlinking, onExitStateBlink },
    [ON_TO_BLINKING] = { STATE_ON, STATE_BLINK, onEntryStateOn, onDoStateOn, onExitStateOn },
    [BLINKING_TO_OFF] = { STATE_BLINK, STATE_OFF, onEntryStateBlink, onDoStateBlinking, onExitStateBlink },
};

void initFSM() {
    currentState = STATE_OFF;
    currentTransition = OFF_TO_BLINKING;
    stateTable[currentTransition].onEnterAction();
}

void runFSM() {
    static bool prevPressed = false;
    bool currPressed = getButton()->isPressed();

    if (currPressed && !prevPressed) {
        stateTable[currentTransition].onExitAction();
        currentState = stateTable[currentTransition].nextState;
        currentTransition = (FSMTransition)((currentTransition + 1) % FSM_TRANSITION_COUNT);
        stateTable[currentTransition].onEnterAction();
    } else {
        stateTable[currentTransition].onDoAction();
    }

    prevPressed = currPressed;
}

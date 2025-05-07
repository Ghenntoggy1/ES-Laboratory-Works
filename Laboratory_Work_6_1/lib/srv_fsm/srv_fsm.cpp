#include "srv_fsm.h"
#include "srv_global_vars.h"
#include <Arduino.h>

FSMState currentState;

void onEntryStateOff() {
    printf("Current State: %s\n", FSMStateStrings[stateTable[OFF_TO_BLINKING].currentState]);
    getLed()->off();
}

void onDoStateOff() { }

void onEntryStateBlink() {
    printf("Current State: %s\n", FSMStateStrings[stateTable[BLINKING_TO_ON].currentState]);
    getLed()->on();
}

void onExitStateOff() {
    printf("Exiting State: %s\n", FSMStateStrings[stateTable[OFF_TO_BLINKING].currentState]);
}

void onDoStateBlinking() {
    static unsigned long lastBlinkTime = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - lastBlinkTime >= 500) {
        getLed()->toggle();
        lastBlinkTime = currentMillis;
    }
}

void onExitStateBlink() {
    printf("Exiting State: %s\n", FSMStateStrings[stateTable[BLINKING_TO_ON].currentState]);
}

void onEntryStateOn() {
    printf("Current State: %s\n", FSMStateStrings[stateTable[ON_TO_OFF].currentState]);
    getLed()->on();
}

void onDoStateOn() { }

void onExitStateOn() {
    printf("Exiting State: %s\n", FSMStateStrings[stateTable[ON_TO_OFF].currentState]);
}


StateTableStruct stateTable[STATE_COUNT] = {
    [OFF_TO_BLINKING] = { STATE_OFF, STATE_BLINK, onEntryStateOff, onDoStateOff, onExitStateOff },
    [BLINKING_TO_ON] = { STATE_BLINK, STATE_ON, onEntryStateBlink, onDoStateBlinking, onExitStateBlink },
    [ON_TO_OFF] = { STATE_ON, STATE_OFF, onEntryStateOn, onDoStateOn, onExitStateOn }
};

void initFSM() {
    currentState = STATE_OFF;
    stateTable[currentState].onEnterAction();
}

void runFSM() {
    static bool prevPressed = false;
    bool currPressed = getButton()->isPressed();

    if (currPressed && !prevPressed) {
        stateTable[currentState].onExitAction();
        currentState = stateTable[currentState].nextState;
        stateTable[currentState].onEnterAction();
    } else {
        stateTable[currentState].onDoAction();
    }

    prevPressed = currPressed;
}

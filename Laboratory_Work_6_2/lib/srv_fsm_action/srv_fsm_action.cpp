#include "srv_fsm_action.h"
#include "srv_global_vars.h"

void eastWestToGreen() {
    globalVariables.eastWestGreenLed->on();
    globalVariables.northSouthRedLed->on();

    globalVariables.eastWestRedLed->off();
    globalVariables.eastWestYellowLed->off();
    globalVariables.northSouthGreenLed->off();
    globalVariables.northSouthYellowLed->off();

    printf("STATE: East West Green\n");
}

void eastWestToYellow() {
    globalVariables.eastWestYellowLed->on();
    globalVariables.northSouthRedLed->on();

    globalVariables.eastWestGreenLed->off();
    globalVariables.eastWestRedLed->off();
    globalVariables.northSouthGreenLed->off();
    globalVariables.northSouthYellowLed->off();

    printf("STATE: East West Yellow\n");
}

void northSouthToGreen() {
    globalVariables.northSouthGreenLed->on();
    globalVariables.eastWestRedLed->on();

    globalVariables.eastWestGreenLed->off();
    globalVariables.eastWestYellowLed->off();
    globalVariables.northSouthRedLed->off();
    globalVariables.northSouthYellowLed->off();

    printf("STATE: North South Green\n");
}

void northSouthToYellow() {
    globalVariables.northSouthYellowLed->on();
    globalVariables.eastWestRedLed->on();

    globalVariables.eastWestGreenLed->off();
    globalVariables.northSouthGreenLed->off();
    globalVariables.northSouthRedLed->off();
    globalVariables.eastWestYellowLed->off();

    printf("STATE: North South Yellow\n");
}

void northSouthRedToYellow() {
    globalVariables.northSouthYellowLed->on();
    globalVariables.eastWestRedLed->on();

    globalVariables.eastWestGreenLed->off();
    globalVariables.northSouthGreenLed->off();
    globalVariables.northSouthRedLed->off();
    globalVariables.eastWestYellowLed->off();

    printf("STATE: North South Red to Yellow\n");
}

void eastWestRedToYellow() {
    globalVariables.eastWestYellowLed->on();
    globalVariables.northSouthRedLed->on();

    globalVariables.eastWestGreenLed->off();
    globalVariables.northSouthGreenLed->off();
    globalVariables.northSouthYellowLed->off();
    globalVariables.eastWestRedLed->off();

    printf("STATE: East West Red to Yellow\n");
}

void toNightModeBlinking() {
    globalVariables.eastWestGreenLed->off();
    globalVariables.northSouthGreenLed->off();
    globalVariables.eastWestRedLed->off();
    globalVariables.northSouthRedLed->off();
    globalVariables.eastWestYellowLed->off();
    globalVariables.northSouthYellowLed->off();
    while (isNightModeActive()) {
        globalVariables.eastWestYellowLed->toggle();
        globalVariables.northSouthYellowLed->toggle();

        vTaskDelay(pdMS_TO_TICKS(NIGHT_MODE_BLINKING_TIME_REC));
    }
    
}
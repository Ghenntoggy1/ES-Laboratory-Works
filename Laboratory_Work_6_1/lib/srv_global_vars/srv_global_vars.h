#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include "dd_button.h"
#include "dd_led.h"

#define LED_PIN 8
#define BUTTON_PIN 9

struct GlobalVariables {
    Led *led;
    Button *button;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

Led *getLed();
Button *getButton();

#endif
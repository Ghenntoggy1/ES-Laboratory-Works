#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include "dd_button.h"
#include "dd_led.h"

#define BUTTON_PIN 8
#define LED_PIN 9
#define OFF_TO_BLINKING_TIME_MS 50
#define ON_TO_BLINKING_TIME_MS 500

struct GlobalVariables {
    Led *led;
    Button *button;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

Led *getLed();
Button *getButton();

#endif
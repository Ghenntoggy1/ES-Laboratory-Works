#include "srv_global_vars.h"
#include <stdio.h>

GlobalVariables globalVariables = {
    .led = new Led(LED_PIN),
    .button = new Button(BUTTON_PIN)
};

void globalVariablesSetup()
{
    globalVariables.led = new Led(LED_PIN);
    globalVariables.button = new Button(BUTTON_PIN);
}

Led *getLed()
{
    return globalVariables.led;
}

Button *getButton()
{
    return globalVariables.button;
}
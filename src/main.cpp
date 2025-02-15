#include <Arduino.h>
#include "main.h"

#define APP_NAME LAB_0

void setup() {
    #if APP_NAME == LAB_0
        setup();
    #endif
}

void loop() {
    #if APP_NAME == LAB_0
        loop();
    #endif
}
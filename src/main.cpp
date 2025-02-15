#include <Arduino.h>
#include "lab_0_main.h"
#include "lab_1_1_main.h"

#define APP_NAME LAB_1_1

void setup() {
    #if APP_NAME == LAB_0
        lab_0_setup();
    #elif APP_NAME == LAB_1_1
        lab_1_1_setup();
    #endif
}

void loop() {
    #if APP_NAME == LAB_0
        lab_0_loop();
    #elif APP_NAME == LAB_1_1
        lab_1_1_loop();
    #endif
}
#include <Arduino.h>
#include "lab_0_main.h"
#include "lab_1_1_main.h"

#define APP_NAME "LAB_1_1"

void setup() {
    if (APP_NAME == "LAB_0") {
        lab_0_setup();
    } else if (APP_NAME == "LAB_1_1") {
        lab_1_1_setup();
    }
}

void loop() {
    if (APP_NAME == "LAB_0") {
        lab_0_loop();
    } else if (APP_NAME == "LAB_1_1") {
        lab_1_1_loop();
    }
}
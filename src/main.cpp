#include <Arduino.h>
#include "lab_0_main.h"
#include "lab_1_1_main.h"
#include "lab_1_2_main.h"
#include "lab_2_1_main.h"

enum AppName {
    LAB_0,
    LAB_1_1,
    LAB_1_2,
    LAB_2_1
};

AppName appName = LAB_2_1;

void setup() {
    switch (appName) {
        case LAB_0:
            lab_0_setup();
            break;
        case LAB_1_1:
            lab_1_1_setup();
            break;
        case LAB_1_2:
            lab_1_2_setup();
            break;
        case LAB_2_1:
            lab_2_1_setup();
            break;
    }
}

void loop() {
    switch (appName) {
        case LAB_0:
            lab_0_loop();
            break;
        case LAB_1_1:
            lab_1_1_loop();
            break;
        case LAB_1_2:
            lab_1_2_loop();
            break;
        case LAB_2_1:
            lab_2_1_loop();
            break;
    }
}
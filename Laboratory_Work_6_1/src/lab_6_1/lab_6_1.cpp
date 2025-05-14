#include "lab_6_1.h"

#include "srv_serial_stdio.h"
#include "srv_fsm.h"
#include "srv_global_vars.h"

void lab_6_1_setup() {
    srvSerialSetup();
    globalVariablesSetup();
    initFSM();
    printf("Lab 6.1 setup done\n");
}

void lab_6_1_loop() {
    runFSM();
    delay(100);
}
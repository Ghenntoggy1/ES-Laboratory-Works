#include "lab_6_2.h"
#include <Arduino_FreeRTOS.h>

#include "srv_global_vars.h"
#include "srv_task_manager.h"
#include "srv_serial_stdio.h"

void lab_6_2_setup() {
    srvSerialSetup();
    globalVariablesSetup();
    printf("Lab 6.2 setup done\n");

    // Create tasks
    xTaskCreate(trafficControlTask, "TrafficControlTask", TRAFFIC_CONTROL_TASK_STACK_SIZE, NULL, TRAFFIC_CONTROL_TASK_PRIORITY, NULL);
    xTaskCreate(requestNorthSouthTask, "RequestNorthSouthTask", REQUEST_NORTH_SOUTH_TASK_STACK_SIZE, NULL, REQUEST_NORTH_SOUTH_TASK_PRIORITY, NULL);
    xTaskCreate(nightModeToggleTask, "NightModeToggleTask", NIGHT_MODE_TOGGLE_TASK_STACK_SIZE, NULL, NIGHT_MODE_TOGGLE_TASK_PRIORITY, NULL);
    xTaskCreate(nightBlinkingTask, "NightBlinkingTask", NIGHT_BLINKING_TASK_STACK_SIZE, NULL, NIGHT_BLINKING_TASK_PRIORITY, NULL);
}

void lab_6_2_loop() {
    // Do nothing
}
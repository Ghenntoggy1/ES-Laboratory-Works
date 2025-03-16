#include "lab_3_1_main.h"
#include <Arduino_FreeRTOS.h>
#include "srv_serial_stdio.h"
#include "srv_global_vars.h"
#include "srv_task_manager.h"

void lab_3_1_setup() {
    srvSerialSetup();
    globalVariablesSetup();
    printf("Lab 3.1 setup done\n");

    xTaskCreate(joystickTask, "joystickTask", JOYSTICK_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(serialReportTask, "serialReportTask", SERIAL_REPORT_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    vTaskStartScheduler();
}

void lab_3_1_loop() {
    // do nothing since FreeRTOS is handling the tasks
}
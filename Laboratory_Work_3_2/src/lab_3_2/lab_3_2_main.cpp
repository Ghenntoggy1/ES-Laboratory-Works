#include "lab_3_2_main.h"
#include "srv_serial_stdio.h"
#include "srv_global_vars.h"
#include "srv_task_manager.h"

void lab_3_2_setup() {
    srvSerialSetup();
    globalVariablesSetup();
    printf("Lab 3.2 setup done\n");

    xTaskCreate(joystickTask, "joystickTask", JOYSTICK_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(serialReportTask, "serialReportTask", SERIAL_REPORT_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    vTaskStartScheduler();
}

void lab_3_2_loop() {
    // do nothing since FreeRTOS is handling the tasks
}
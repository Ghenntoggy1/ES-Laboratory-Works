#include "lab_4_2.h"
#include <Arduino_FreeRTOS.h>

#include "srv_task_manager.h"
#include "srv_global_vars.h"
#include "srv_serial_stdio.h"

void lab_4_2_setup() {
    srvSerialSetup();
    globalVariablesSetup();
    printf("Lab 4.2 setup done\n");

    // Create tasks
    xTaskCreate(serialReportTask, "SerialReport", SERIAL_REPORT_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(commandHandlerTask, "CommandHandler", COMMAND_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
}

void lab_4_2_loop() {
    // Do nothing
}
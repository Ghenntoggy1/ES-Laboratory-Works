#include "lab_5_1.h"
#include <Arduino_FreeRTOS.h>

#include "srv_task_manager.h"
#include "srv_global_vars.h"
#include "srv_serial_stdio.h"

void lab_5_1_setup() {
    srvSerialSetup();
    globalVariablesSetup();
    printf("Lab 5.1 setup done\n");

    // Create tasks
    xTaskCreate(motorUpdateTask, "MotorControlTask", MOTOR_CONTROL_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(commandHandlerTask, "CommandHandler", COMMAND_HANDLER_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(serialReportTask, "SerialReportTask", SERIAL_REPORT_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
}

void lab_5_1_loop() {
    // Do nothing
}
#include "lab_4_1.h"
#include "srv_serial_stdio.h"
#include <Arduino_FreeRTOS.h>
#include "dd_relay.h"
#include "srv_task_manager.h"
#include "srv_global_vars.h"

void lab_4_1_setup() {
    srvSerialSetup();
    globalVariablesSetup();
    printf("Lab 4.1 setup done\n");
    // Create tasks

    xTaskCreate(serialReportTask, "SerialReport", SERIAL_REPORT_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(commandHandlerTask, "CommandHandler", COMMAND_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

}

void lab_4_1_loop() {
    // do nothing
}


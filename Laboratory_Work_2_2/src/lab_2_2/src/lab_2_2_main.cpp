#include "lab_2_2_main.h"
#include <Arduino_FreeRTOS.h>
#include "srv_serial_stdio.h"
#include "srv_global_vars/srv_global_vars.h"
#include "srv_task_manager/srv_task_manager.h"

void lab_2_2_setup() {
    srvSerialSetup();
    globalVariablesSetup();

    xTaskCreate(buttonT1, "buttonT1", BUTTON_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(syncT2, "syncT2", SYNC_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(asyncT3, "asyncT3", ASYNC_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(blinkT4, "blinkT4", ASYNC_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    vTaskStartScheduler();
}

void lab_2_2_loop() {
    // do nothing since FreeRTOS is handling the tasks
}
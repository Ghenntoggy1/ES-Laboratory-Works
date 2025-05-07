#include "srv_task_manager.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include <stdio.h>
#include "srv_global_vars.h"
#include <stdlib.h>

void ledControlTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1) {
        int FSM_State = getFSMState();
        
        // int currentButtonState = getButton()->isPressed() ? BUTTON_LOW : BUTTON_HIGH;
        // setButtonState(currentButtonState);
        
        int output = FSM[FSM_State].Out;
        setLedState(output);
        getLed()->setState(output);
        printf("LED State: %d\n", output);
        
        int delayTime = FSM[FSM_State].Time;

        int input = getButton()->readInput();
        setButtonState(input);
        printf("Button State: %d\n", input);

        FSM_State = FSM[FSM_State].Next[input];
        setFSMState(FSM_State);
        printf("Next FSM State: %d\n", FSM_State);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(SERIAL_REPORT_TASK_REC_MS));
    }
}

void serialReportTask(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1) {
        // Report status 
        if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
            printf("FSM Current State: %d\n", getFSMState());
            printf("LED Current State: %d\n", getLedState());
            printf("Button Current State: %d\n", getButtonState());
            
            xSemaphoreGive(getSerialMutex());
        }
        
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(SERIAL_REPORT_TASK_REC_MS));
    }
}
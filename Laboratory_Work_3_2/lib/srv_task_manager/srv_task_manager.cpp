#include "srv_task_manager.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include <stdio.h>
#include "srv_global_vars.h"

void joystickTask(void* pvParameters)
{
    TickType_t snapshotTick = xTaskGetTickCount();
    const TickType_t joystickRecTicks = pdMS_TO_TICKS(JOYSTICK_TASK_REC_MS);

    while (1) {
        int x = globalVariables.joystick->getX();
        int y = globalVariables.joystick->getY();
        bool button = globalVariables.joystick->getButtonState();
        
        if (xSemaphoreTake(globalVariables.joystickMutex, portMAX_DELAY) == pdTRUE) {
            globalVariables.globalJoystickXValue = x;
            globalVariables.globalJoystickYValue = y;
            globalVariables.globalJoystickButtonState = button;
            xSemaphoreGive(globalVariables.joystickMutex);
        }

        xTaskDelayUntil(&snapshotTick, joystickRecTicks);
    }
}

void serialReportTask(void* pvParameters)
{
    TickType_t snapshotTick = xTaskGetTickCount();
    const TickType_t serialReportRecTicks = pdMS_TO_TICKS(SERIAL_REPORT_TASK_REC_MS);
    
    int localX = 0;
    int localY = 0;
    bool localButton = false;

    while (1) {
        if (xSemaphoreTake(globalVariables.joystickMutex, portMAX_DELAY) == pdTRUE) 
        {
            localX = globalVariables.globalJoystickXValue;
            localY = globalVariables.globalJoystickYValue;
            localButton = globalVariables.globalJoystickButtonState;
            xSemaphoreGive(globalVariables.joystickMutex);
        }

        if (xSemaphoreTake(globalVariables.serialMutex, portMAX_DELAY) == pdTRUE) 
        {
            printf("STATUS REPORT:\n");
            printf("X: %d\n", localX);
            printf("Y: %d\n", localY);
            printf("Button: %d\n", localButton);
            if (localX > THRESHOLD_X_RUN) {
                globalVariables.ledLeft->off();
                globalVariables.ledRight->on();
                printf("Running Right\n");
            } else if (localX > THRESHOLD_X_STAND) {
                globalVariables.ledLeft->off();
                globalVariables.ledRight->on();
                printf("Walking Right\n");
            } else if (localX < -THRESHOLD_X_RUN) {
                globalVariables.ledRight->off();
                globalVariables.ledLeft->on();
                printf("Running Left\n");
            } else if (localX < -THRESHOLD_X_STAND) {
                globalVariables.ledRight->off();
                globalVariables.ledLeft->on();
                printf("Walking Left\n");
            } else {
                globalVariables.ledRight->off();
                globalVariables.ledLeft->off();
            }
        
            if (localY > THRESHOLD_Y_RUN) {
                globalVariables.ledBackward->off();
                globalVariables.ledForward->on();
                printf("Running Forward\n");
            } else if (localY > THRESHOLD_Y_STAND) {
                globalVariables.ledBackward->off();
                globalVariables.ledForward->on();
                printf("Walking Forward\n");
            } else if (localY < -THRESHOLD_Y_RUN) {
                globalVariables.ledForward->off();
                globalVariables.ledBackward->on();
                printf("Running Backwards\n");
            } else if (localY < -THRESHOLD_Y_STAND) {
                globalVariables.ledForward->off();
                globalVariables.ledBackward->on();
                printf("Walking Backwards\n");
            } else {
                globalVariables.ledForward->off();
                globalVariables.ledBackward->off();
            }
        
            if (localX >= -THRESHOLD_X_STAND && localX <= THRESHOLD_X_STAND && localY >= -THRESHOLD_Y_STAND && localY <= THRESHOLD_Y_STAND) {
                
                printf("Standing\n");
            }

            xSemaphoreGive(globalVariables.serialMutex);
        }

        xTaskDelayUntil(&snapshotTick, serialReportRecTicks);
    }
}
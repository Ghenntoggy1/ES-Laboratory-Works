#include "srv_task_manager.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include <stdio.h>
#include "srv_global_vars.h"

void serialReportTask(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    while (1) {
        // Try to take the mutex but don't wait forever
        if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
            printf("System status: Relay is %s\n", getRelay()->isOn() ? "ON" : "OFF");
            xSemaphoreGive(getSerialMutex());
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(SERIAL_REPORT_TASK_REC_MS));
    }
}

void commandHandlerTask(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    char input[20];
    uint8_t index = 0;

    while (1) {
        if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
            printf("> ");
            
            while (1) {
                char c;
                scanf("%c", &c);
                printf("%c", c);
                
                if (c == '\n' || c == '\r') {
                    input[index] = '\0';
                    break;
                }
                else if (index < sizeof(input) - 1) {
                    input[index++] = c;
                }
            }
            
            if (strcmp(input, "relay on") == 0) {
                getRelay()->on();
                printf("Relay turned ON\n");
            } 
            else if (strcmp(input, "relay off") == 0) {
                getRelay()->off();
                printf("Relay turned OFF\n");
            }
            else if (strlen(input) > 0) {
                printf("Unknown command. Use 'relay on' or 'relay off'\n");
            }
            
            index = 0;
            memset(input, 0, sizeof(input));
            
            xSemaphoreGive(getSerialMutex());
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(COMMAND_TASK_REC_MS));
    }
}
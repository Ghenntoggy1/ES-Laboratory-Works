#include "srv_task_manager.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include <stdio.h>
#include "srv_global_vars.h"

void serialReportTask(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    while (1) {
        if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
            DCMotor* motorA = getMotorA();
            if (motorA) {
                printf("Motor A Power: %d\n", motorA->get_power());
                printf("Motor A Direction: %s\n", motorA->is_going_forward().c_str());
            } else {
                printf("Motor A not initialized\n");
            }
            
            xSemaphoreGive(getSerialMutex());
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(SERIAL_REPORT_TASK_REC_MS));
    }
}

void commandHandlerTask(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    char command[100];
    uint8_t index = 0;

    while (1) {
        while (1) {
            char c;
            scanf("%c", &c);

            if (c == '\n' || c == '\r') {
                command[index] = '\0';
                break;
            } else if (index < sizeof(command) - 1) {
                command[index++] = c;
            }
        }

        if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
            if (strncmp(command, "motor set ", 10) == 0) {
                int val = atoi(&command[10]);
                printf("Setting motor to %d%% power\n", val);
                if (val < -100 || val > 100) {
                    printf("Warning: Invalid value. Must be between -100 and 100.\n");
                } else {
                    getMotorA()->set_power(val);
                    printf("Motor set to %d%% power\n", val);
                }
            } else if (strcmp(command, "motor stop") == 0) {
                getMotorA()->stop_motor();
                printf("Motor stopped\n");
            } else if (strcmp(command, "motor inc") == 0) {
                int currentPower = getMotorA()->get_power();
                if (currentPower == 100 || currentPower == -100) {
                    printf("Warning: Motor already at Maximum power\n");
                } else {
                    int increment = (currentPower >= 0) ? 10 : -10;
                    getMotorA()->set_power(currentPower + increment);
                    printf("Motor increased to %d%%\n", currentPower + increment);
                }
            } else if (strcmp(command, "motor dec") == 0) {
                int currentPower = getMotorA()->get_power();
                if (currentPower == 0) {
                    printf("Warning: Motor already at Minimum power\n");
                } else {
                    int decrement = (currentPower >= 0) ? 10 : -10;
                    getMotorA()->set_power(currentPower - decrement);
                    printf("Motor increased to %d%%\n", currentPower - decrement);
                }
            } else if (strcmp(command, "motor max") == 0) {
                int sign = getMotorA()->get_power() >= 0 ? 1 : -1;
                getMotorA()->set_power(sign * 100);
                printf("Motor set to maximum (%d%%)\n", getMotorA()->get_power());
            } else if (strlen(command) > 0) {
                printf("Unknown command.\n");
                printf("Try: motor set [value], motor stop, motor inc, motor dec, motor max\n");
            }

            index = 0;
            xSemaphoreGive(getSerialMutex());
        }

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(COMMAND_TASK_REC_MS));
    }
}

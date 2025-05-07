#include "srv_task_manager.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include <stdio.h>
#include "srv_global_vars.h"
#include "dd_servo_motor.h"

void motorUpdateTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1) {
        int feedbackValue = globalVariables.servoMotor->readFeedback();
        float error = globalVariables.servoMotor->getSetpoint() - feedbackValue;
        
        globalVariables.servoMotor->setIntegral(globalVariables.servoMotor->getIntegral() + error);
        
        float derivative = error - globalVariables.servoMotor->getPrevError();
        
        float output = globalVariables.servoMotor->getKp() * error + 
        globalVariables.servoMotor->getKi() * globalVariables.servoMotor->getIntegral() + 
        globalVariables.servoMotor->getKd() * derivative;

        globalVariables.servoMotor->setOutput(constrain(output, 0, 180));

        globalVariables.servoMotor->setPrevError(error);

        globalVariables.servoMotor->setPosition(globalVariables.servoMotor->getOutput());
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(MOTOR_CONTROL_TASK_REC_MS));
    }
}

void serialReportTask(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1) {
        // Report status 
        if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
            ServoMotor* servoMotor = getServoMotor();
            if (servoMotor) {
                char buf[10];
                dtostrf(servoMotor->getSetpoint(), 6, 2, buf);
                printf("%s\t", buf);
                dtostrf(servoMotor->getFeedback(), 6, 2, buf);
                printf("%s\t", buf);
                dtostrf(servoMotor->getOutput(), 6, 2, buf);
                printf("%s\n", buf);
            } else {
                printf("Servo Motor not initialized\n");
            }
            
            xSemaphoreGive(getSerialMutex());
        }
        
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(SERIAL_REPORT_TASK_REC_MS));
    }
}


void commandHandlerTask(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    char command[100];

    if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
        printf("Distance Control using PID Control\n");
        printf("- set <value>   - Set Target Distance\n");
        xSemaphoreGive(getSerialMutex());
    }

    while (1) {
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;
        if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
            if (strncmp(command, "set ", 4) == 0) {
                char buf[10];
                float val = atof(&command[4]);
                if (val < 0 || val > 180) {
                    printf("Warning: Invalid value. Must be between 0 and 180.\n");
                } else {
                    globalVariables.servoMotor->setSetpoint(val);
                    dtostrf(val, 6, 2, buf);
                    printf("Target distance set to %s\n", buf);
                }
            } else {
                printf("Unknown command.\n");
                printf("Try: set <val>\n");
            }

            xSemaphoreGive(getSerialMutex());
        }

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(COMMAND_HANDLER_TASK_STACK_SIZE));
    }
}
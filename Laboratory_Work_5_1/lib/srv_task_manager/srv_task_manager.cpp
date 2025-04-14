#include "srv_task_manager.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include <stdio.h>
#include "srv_global_vars.h"

void motorUpdateTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1) {
        float currentDistance = globalVariables.ultrasonicSensor->getDistance();
        float setpoint = globalVariables.ultrasonicSensor->getSetpoint();
        float hysteresis = globalVariables.ultrasonicSensor->getHysteresisBand();
        float upperThreshold = setpoint + hysteresis;
        float lowerThreshold = setpoint - hysteresis;

        if (currentDistance > upperThreshold) {
            globalVariables.motorA->set_power(-20);
            globalVariables.ledHystHigh->on();
            globalVariables.ledHystLow->off();
            if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
                xSemaphoreGive(getSerialMutex());
            }
        } else if (currentDistance < lowerThreshold) {
            globalVariables.motorA->set_power(20);
            globalVariables.ledHystHigh->off();
            globalVariables.ledHystLow->on();
            if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
                xSemaphoreGive(getSerialMutex());
            }
        } else {
            globalVariables.motorA->stop_motor();
            globalVariables.ledHystHigh->off();
            globalVariables.ledHystLow->off();
            if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
                xSemaphoreGive(getSerialMutex());
            }
        }

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(MOTOR_CONTROL_TASK_REC_MS));
    }
}

void serialReportTask(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1) {
        // Report status 
        if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
            DCMotor* motorA = getMotorA();
            DD_ULTRASONIC* ultrasonicSensor = globalVariables.ultrasonicSensor;
            if (ultrasonicSensor) {
                char buf[10];
                dtostrf(ultrasonicSensor->getDistance(), 6, 2, buf);
                printf("Current Distance: %s\n", buf);
                dtostrf(ultrasonicSensor->getSetpoint(), 6, 2, buf);
                printf("Setpoint: %s\n", buf);
                dtostrf(ultrasonicSensor->getHysteresisBand(), 6, 2, buf);
                printf("Hysteresis: %s\n", buf);
            } else {
                printf("Ultrasonic Sensor not initialized\n");
            }
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

    if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
        printf("Distance Control using On/Off Hysteresis\n");
        printf("- set <value>   - Set Target Distance\n");
        printf("- hyst <value>  - Set Hysteresis Band\n");
        xSemaphoreGive(getSerialMutex());
    }

    while (1) {
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;
        if (xSemaphoreTake(getSerialMutex(), portMAX_DELAY) == pdTRUE) {
            if (strncmp(command, "set ", 4) == 0) {
                char buf[10];
                float val = atof(&command[4]);
                globalVariables.ultrasonicSensor->setTargetSetpoint(val);
                dtostrf(val, 6, 2, buf);
                printf("Target distance set to %s\n", buf);
            } else if (strncmp(command, "hyst ", 5) == 0) {
                char buf[10];
                float val = atof(&command[5]);
                globalVariables.ultrasonicSensor->setHysteresisBand(val);
                dtostrf(val, 6, 2, buf);
                printf("Hysteresis band set to %s\n", buf);
            } else {
                printf("Unknown command.\n");
                printf("Try: set <val>, hyst <val>\n");
            }

            xSemaphoreGive(getSerialMutex());
        }

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(COMMAND_HANDLER_TASK_STACK_SIZE));
    }
}
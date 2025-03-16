#include "srv_task_manager.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include <stdio.h>
#include "../srv_global_vars/srv_global_vars.h"

void buttonT1(void* pvParameters)
{
    TickType_t snapshotTick = xTaskGetTickCount();
    const TickType_t buttonT1RecTicks = pdMS_TO_TICKS(BUTTON_T1_REC_MS);

    while (1) {
        if (getButtonState()) {
            xSemaphoreGive(getButtonT1Semaphore());
            globalVariables.led1->on();
            vTaskDelay(pdMS_TO_TICKS(LED_1_ON_TIME_MS));
            globalVariables.led1->off();
        }

        xTaskDelayUntil(&snapshotTick, buttonT1RecTicks); 
    }
}

void syncT2(void* pvParameters)
{
    while (1) {
        if (xSemaphoreTake(getButtonT1Semaphore(), portMAX_DELAY)) {
            if (xSemaphoreTake(getCounterMutex(), portMAX_DELAY) == pdTRUE) {
                globalVariables.counter++;  // N = N + 1
                xSemaphoreGive(getCounterMutex());
            }

            for (int i = 1; i <= globalVariables.counter; i++) {
                xQueueSendToFront(getProducerConsumerQueue(), &i, portMAX_DELAY);
            }

            for (int i = 0; i < globalVariables.counter; i++) {
                globalVariables.led2->on();
                vTaskDelay(pdMS_TO_TICKS(LED_2_ON_TIME_MS));
                globalVariables.led2->off();
                vTaskDelay(pdMS_TO_TICKS(LED_2_OFF_TIME_MS));
            }

            vTaskDelay(pdMS_TO_TICKS(SYNC_T2_REC_MS));
        }
    }
}

void asyncT3(void* pvParameters)
{
    int queueData;

    while (1) {
        if (xQueueReceive(getProducerConsumerQueue(), &queueData, portMAX_DELAY)) {
            if (xSemaphoreTake(globalVariables.serialMutex, portMAX_DELAY) == pdTRUE) {
                printf("N = %d: LED1 guided by Button ON!\n", queueData);
                xSemaphoreGive(globalVariables.serialMutex);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(ASYNC_T3_REC_MS));  // 200ms Recurrency
    }
}

// New task that will blink 3 times both LEDs. Use Serial mutex to avoid conflicts with other tasks.
void blinkT4(void* pvParameters)
{
    TickType_t snapshotTick = xTaskGetTickCount();
    const TickType_t blinkT4RecTicks = pdMS_TO_TICKS(BLINK_T4_REC_MS);

    while (1) {
        if (xSemaphoreTake(globalVariables.serialMutex, portMAX_DELAY) == pdTRUE) {
            for (int i = 0; i < 3; i++) {
                printf("Blinking LEDs 1 and 2\n");
                globalVariables.led1->on();
                globalVariables.led2->on();
                vTaskDelay(pdMS_TO_TICKS(BLINK_T4_ON_TIME_MS));
                globalVariables.led1->off();
                globalVariables.led2->off();
                vTaskDelay(pdMS_TO_TICKS(BLINK_T4_OFF_TIME_MS));
            }
            xSemaphoreGive(globalVariables.serialMutex);
        }

        xTaskDelayUntil(&snapshotTick, blinkT4RecTicks);
    }
}
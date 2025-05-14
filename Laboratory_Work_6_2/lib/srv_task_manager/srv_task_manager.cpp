#include <Arduino_FreeRTOS.h>
#include "srv_task_manager.h"
#include <semphr.h>
#include <queue.h>
#include <stdio.h>
#include "srv_global_vars.h"
#include "srv_fsm.h"
#include "srv_fsm_action.h"

void trafficControlTask(void* pvParameters) {
    TickType_t lastWake = xTaskGetTickCount();
    int state = getCurrentState();
    bool isSuspendedForNightMode = false;

    while (1) {
        if (isNightModeActive()) {
            if (!isSuspendedForNightMode) {
                isSuspendedForNightMode = true;
            }
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }

        if (isSuspendedForNightMode) {
            lastWake = xTaskGetTickCount();
            FSMStatesStruct[state].onEntryAction();
            isSuspendedForNightMode = false;
        }

        xSemaphoreTake(getStateMutex(), pdMS_TO_TICKS(10));
        setCurrentState(state);
        xSemaphoreGive(getStateMutex());

        FSMStatesStruct[state].onEntryAction();
        vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(FSMStatesStruct[state].time));

        switch (state) {
            case STATE_EAST_WEST_GREEN:
                if (isNorthSouthRequested()) {
                    printf("NEXT STATE: North South Entry Yellow\n");
                    state = STATE_EAST_WEST_YELLOW;
                    setNorthSouthRequest(false);
                }
                break;
            case STATE_EAST_WEST_YELLOW:
                printf("NEXT STATE: North South Entry Yellow\n");
                state = STATE_NORTH_SOUTH_ENTRY_YELLOW;
                break;
            case STATE_NORTH_SOUTH_ENTRY_YELLOW:
                printf("NEXT STATE: North South Green\n");
                state = STATE_NORTH_SOUTH_GREEN;
                break;
            case STATE_NORTH_SOUTH_GREEN:
                printf("NEXT STATE: North South Yellow\n");
                state = STATE_NORTH_SOUTH_YELLOW;
                break;
            case STATE_NORTH_SOUTH_YELLOW:
                printf("NEXT STATE: East West Entry Yellow\n");
                state = STATE_EAST_WEST_ENTRY_YELLOW;
                break;
            case STATE_EAST_WEST_ENTRY_YELLOW:
                printf("NEXT STATE: East West Green\n");
                state = STATE_EAST_WEST_GREEN;
                break;
        }
    }
}

void requestNorthSouthTask(void* pvParameters) {
    while (1) {
        if (getSwitchDirectionButton()->isPressed()) {
            setNorthSouthRequest(true);

            vTaskDelay(pdMS_TO_TICKS(200));

        }
        vTaskDelay(pdMS_TO_TICKS(REQUEST_NORTH_SOUTH_TASK_REC_MS));
    }
}

void nightModeToggleTask(void* pvParameters) {
    while (1) {
        if (getNightModeButton()->isPressed()) {
            setNightModeActive(!isNightModeActive());
            printf(isNightModeActive() ? "INTERMITENT STATE: NIGHT MODE ON\r\n" : "INTERMITENT STATE: NIGHT MODE OFF\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(NIGHT_MODE_TOGGLE_TASK_REC_MS));
    }
}

void nightBlinkingTask(void* pvParameters) {
    while (1) {
        if (isNightModeActive()) {
            toNightModeBlinking();
            vTaskDelay(pdMS_TO_TICKS(NIGHT_BLINKING_TASK_REC_MS));
        } 
        else {
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}
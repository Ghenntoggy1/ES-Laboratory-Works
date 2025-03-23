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

        int rawX = globalVariables.joystick->getRawX();
        int rawY = globalVariables.joystick->getRawY();
        int milliVoltX = globalVariables.joystick->getMilliVoltX();
        int milliVoltY = globalVariables.joystick->getMilliVoltY();
        int satMilliVoltX = globalVariables.joystick->getSatMilliVoltX();
        int satMilliVoltY = globalVariables.joystick->getSatMilliVoltY();
        int saltPiperFilteredMilliVoltX = globalVariables.joystick->getSaltPiperFilteredMilliVoltX();
        int saltPiperFilteredMilliVoltY = globalVariables.joystick->getSaltPiperFilteredMilliVoltY();
        int weightedAverageFilteredMilliVoltX = globalVariables.joystick->getWeightedAverageFilteredMilliVoltX();
        int weightedAverageFilteredMilliVoltY = globalVariables.joystick->getWeightedAverageFilteredMilliVoltY();
        int physicalX = globalVariables.joystick->getPhysicalX();
        int physicalY = globalVariables.joystick->getPhysicalY();

        bool button = globalVariables.joystick->getButtonState();
        
        if (xSemaphoreTake(globalVariables.joystickMutex, portMAX_DELAY) == pdTRUE) {
            globalVariables.globalJoystickXValue = x;
            globalVariables.globalJoystickYValue = y;

            globalVariables.globalJoystickRawXValue = rawX;
            globalVariables.globalJoystickRawYValue = rawY;
            globalVariables.globalJoystickMilliVoltXValue = milliVoltX;
            globalVariables.globalJoystickMilliVoltYValue = milliVoltY;
            globalVariables.globalJoystickSatMilliVoltXValue = satMilliVoltX;
            globalVariables.globalJoystickSatMilliVoltYValue = satMilliVoltY;
            globalVariables.globalJoystickSaltPiperFilteredMilliVoltXValue = saltPiperFilteredMilliVoltX;
            globalVariables.globalJoystickSaltPiperFilteredMilliVoltYValue = saltPiperFilteredMilliVoltY;
            globalVariables.globalJoystickWeightedAverageFilteredMilliVoltXValue = weightedAverageFilteredMilliVoltX;
            globalVariables.globalJoystickWeightedAverageFilteredMilliVoltYValue = weightedAverageFilteredMilliVoltY;
            globalVariables.globalJoystickPhysicalXValue = physicalX;
            globalVariables.globalJoystickPhysicalYValue = physicalY;

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
    
    int localRawX = 0;
    int localRawY = 0;
    int localMilliVoltX = 0;
    int localMilliVoltY = 0;
    int localSatMilliVoltX = 0;
    int localSatMilliVoltY = 0;
    int localSaltPiperFilteredMilliVoltX = 0;
    int localSaltPiperFilteredMilliVoltY = 0;
    int localWeightedAverageFilteredMilliVoltX = 0;
    int localWeightedAverageFilteredMilliVoltY = 0;
    int localPhysicalX = 0;
    int localPhysicalY = 0;

    bool localButton = false;

    while (1) {
        if (xSemaphoreTake(globalVariables.joystickMutex, portMAX_DELAY) == pdTRUE) 
        {
            localX = globalVariables.globalJoystickXValue;
            localY = globalVariables.globalJoystickYValue;

            localRawX = globalVariables.globalJoystickRawXValue;
            localRawY = globalVariables.globalJoystickRawYValue;
            localMilliVoltX = globalVariables.globalJoystickMilliVoltXValue;
            localMilliVoltY = globalVariables.globalJoystickMilliVoltYValue;
            localSatMilliVoltX = globalVariables.globalJoystickSatMilliVoltXValue;
            localSatMilliVoltY = globalVariables.globalJoystickSatMilliVoltYValue;
            localSaltPiperFilteredMilliVoltX = globalVariables.globalJoystickSaltPiperFilteredMilliVoltXValue;
            localSaltPiperFilteredMilliVoltY = globalVariables.globalJoystickSaltPiperFilteredMilliVoltYValue;
            localWeightedAverageFilteredMilliVoltX = globalVariables.globalJoystickWeightedAverageFilteredMilliVoltXValue;
            localWeightedAverageFilteredMilliVoltY = globalVariables.globalJoystickWeightedAverageFilteredMilliVoltYValue;
            localPhysicalX = globalVariables.globalJoystickPhysicalXValue;
            localPhysicalY = globalVariables.globalJoystickPhysicalYValue;

            localButton = globalVariables.globalJoystickButtonState;
            xSemaphoreGive(globalVariables.joystickMutex);
        }

        if (xSemaphoreTake(globalVariables.serialMutex, portMAX_DELAY) == pdTRUE) 
        {
            printf("STATUS REPORT:\n");
            printf("Raw X: %d | mVolt X: %d mV | Sat. X: %d mV | S.P.Fltr. X: %d | W.A.Fltr. X: %d | Phy. X: %d\n", localRawX, localMilliVoltX, localSatMilliVoltX, localSaltPiperFilteredMilliVoltX, localWeightedAverageFilteredMilliVoltX, localPhysicalX);
            printf("Raw Y: %d | mVolt Y: %d mV | Sat. Y: %d mV | S.P.Fltr. Y: %d | W.A.Fltr. Y: %d | Phy. Y: %d\n", localRawY, localMilliVoltY, localSatMilliVoltY, localSaltPiperFilteredMilliVoltY, localWeightedAverageFilteredMilliVoltY, localPhysicalY);
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
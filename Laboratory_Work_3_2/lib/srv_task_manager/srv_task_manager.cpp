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

void potentiometerTask(void* pvParameters)
{
    TickType_t snapshotTick = xTaskGetTickCount();
    const TickType_t potentiometerRecTicks = pdMS_TO_TICKS(POTENTIOMETER_TASK_REC_MS);

    while (1) {
        int potValue = globalVariables.potentiometer->getPotValue();

        int rawPotValue = globalVariables.potentiometer->getRawPotValue();
        int milliVoltPotValue = globalVariables.potentiometer->getPotMilliVolt();
        int satMilliVoltPotValue = globalVariables.potentiometer->getPotSatMilliVolt();
        int saltPiperFilteredMilliVoltPotValue = globalVariables.potentiometer->getPotSaltPiperFilteredMilliVolt();
        int weightedAverageFilteredMilliVoltPotValue = globalVariables.potentiometer->getPotWeightedAverageFilteredMilliVolt();
        int physicalPotValue = globalVariables.potentiometer->getPotPhysical();

        if (xSemaphoreTake(globalVariables.potentiometerMutex, portMAX_DELAY) == pdTRUE) {
            globalVariables.globalPotentiometerValue = potValue;

            globalVariables.globalPotentiometerRawValue = rawPotValue;
            globalVariables.globalPotentiometerMilliVoltValue = milliVoltPotValue;
            globalVariables.globalPotentiometerSatMilliVoltValue = satMilliVoltPotValue;
            globalVariables.globalPotentiometerSaltPiperFilteredMilliVoltValue = saltPiperFilteredMilliVoltPotValue;
            globalVariables.globalPotentiometerWeightedAverageFilteredMilliVoltValue = weightedAverageFilteredMilliVoltPotValue;
            globalVariables.globalPotentiometerPhysicalValue = physicalPotValue;

            globalVariables.ledPotentiometer->analog(physicalPotValue);

            xSemaphoreGive(globalVariables.potentiometerMutex);
        }
        
        xTaskDelayUntil(&snapshotTick, potentiometerRecTicks);
    }
}

void serialReportTask(void* pvParameters)
{
    TickType_t snapshotTick = xTaskGetTickCount();
    const TickType_t serialReportRecTicks = pdMS_TO_TICKS(SERIAL_REPORT_TASK_REC_MS);
    
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

    int localRawPotValue = 0;
    int localMilliVoltPotValue = 0;
    int localSatMilliVoltPotValue = 0;
    int localSaltPiperFilteredMilliVoltPotValue = 0;
    int localWeightedAverageFilteredMilliVoltPotValue = 0;
    int localPhysicalPotValue = 0;

    bool localButton = false;

    while (1) {
        if (xSemaphoreTake(globalVariables.joystickMutex, portMAX_DELAY) == pdTRUE) 
        {
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

            localRawPotValue = globalVariables.globalPotentiometerRawValue;
            localMilliVoltPotValue = globalVariables.globalPotentiometerMilliVoltValue;
            localSatMilliVoltPotValue = globalVariables.globalPotentiometerSatMilliVoltValue;
            localSaltPiperFilteredMilliVoltPotValue = globalVariables.globalPotentiometerSaltPiperFilteredMilliVoltValue;
            localWeightedAverageFilteredMilliVoltPotValue = globalVariables.globalPotentiometerWeightedAverageFilteredMilliVoltValue;
            localPhysicalPotValue = globalVariables.globalPotentiometerPhysicalValue;


            localButton = globalVariables.globalJoystickButtonState;
            xSemaphoreGive(globalVariables.joystickMutex);
        }

        if (xSemaphoreTake(globalVariables.serialMutex, portMAX_DELAY) == pdTRUE) 
        {
            printf("STATUS REPORT:\n");
            printf("Raw X: %d | mVolt X: %d mV | Sat. X: %d mV | S.P.Fltr. X: %d | W.A.Fltr. X: %d | Phy. X: %d\n", localRawX, localMilliVoltX, localSatMilliVoltX, localSaltPiperFilteredMilliVoltX, localWeightedAverageFilteredMilliVoltX, localPhysicalX);
            printf("Raw Y: %d | mVolt Y: %d mV | Sat. Y: %d mV | S.P.Fltr. Y: %d | W.A.Fltr. Y: %d | Phy. Y: %d\n", localRawY, localMilliVoltY, localSatMilliVoltY, localSaltPiperFilteredMilliVoltY, localWeightedAverageFilteredMilliVoltY, localPhysicalY);
            printf("Button: %d\n", localButton);
            printf("Raw PotValue: %d | mVolt PotValue: %d mV | Sat. PotValue: %d mV | S.P.Fltr. PotValue: %d | W.A.Fltr. PotValue: %d | Phy. PotValue: %d\n", localRawPotValue, localMilliVoltPotValue, localSatMilliVoltPotValue, localSaltPiperFilteredMilliVoltPotValue, localWeightedAverageFilteredMilliVoltPotValue, localPhysicalPotValue);
            xSemaphoreGive(globalVariables.serialMutex);
        }

        xTaskDelayUntil(&snapshotTick, serialReportRecTicks);
    }
}
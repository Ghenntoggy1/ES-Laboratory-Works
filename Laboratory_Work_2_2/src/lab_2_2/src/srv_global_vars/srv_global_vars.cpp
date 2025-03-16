#include "srv_global_vars.h"
#include <stdio.h>
#include <Arduino.h>

GlobalVariables globalVariables = {
    .led1 = nullptr,
    .led2 = nullptr,
    .button = nullptr,
    .buttonT1Semaphore = NULL,
    .producerConsumerQueue = NULL,
    .counterMutex = NULL,
    .serialMutex = NULL,
    .counter = 0,
};

void globalVariablesSetup()
{
    globalVariables.led1 = new Led(LED_1_PIN);
    globalVariables.led2 = new Led(LED_2_PIN);
    globalVariables.button = new Button(BUTTON_PIN);

    globalVariables.led1->off();
    globalVariables.led2->off();

    globalVariables.buttonT1Semaphore = xSemaphoreCreateBinary();
    globalVariables.producerConsumerQueue = xQueueCreate(20, sizeof(int));
    globalVariables.counterMutex = xSemaphoreCreateMutex();
    globalVariables.serialMutex = xSemaphoreCreateMutex();
}

bool getLed1State()
{
    return globalVariables.led1->getState();
}

bool getLed2State()
{
    return globalVariables.led2->getState();
}

bool getButtonState()
{
    return globalVariables.button->isPressed();
}

SemaphoreHandle_t getButtonT1Semaphore()
{
    return globalVariables.buttonT1Semaphore;
}

QueueHandle_t getProducerConsumerQueue()
{
    return globalVariables.producerConsumerQueue;
}

SemaphoreHandle_t getCounterMutex()
{
    return globalVariables.counterMutex;
}

SemaphoreHandle_t getSerialMutex()
{
    return globalVariables.serialMutex;
}
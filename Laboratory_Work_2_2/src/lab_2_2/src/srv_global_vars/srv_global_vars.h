#ifndef SRV_GLOBAL_STATES_H
#define SRV_GLOBAL_STATES_H

#include "dd_led.h"
#include "dd_button.h"
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

#define LED_1_PIN 12
#define LED_2_PIN 13
#define BUTTON_PIN 11

struct GlobalVariables {
    Led *led1;
    Led *led2;
    Button *button;
    SemaphoreHandle_t buttonT1Semaphore;
    QueueHandle_t producerConsumerQueue;
    SemaphoreHandle_t counterMutex;
    SemaphoreHandle_t serialMutex;
    int counter;
};

extern GlobalVariables globalVariables;

void globalVariablesSetup();

bool getLed1State();
bool getLed2State();
bool getButtonState();
SemaphoreHandle_t getButtonT1Semaphore();
QueueHandle_t getProducerConsumerQueue();
SemaphoreHandle_t getCounterMutex();
SemaphoreHandle_t getSerialMutex();

#endif
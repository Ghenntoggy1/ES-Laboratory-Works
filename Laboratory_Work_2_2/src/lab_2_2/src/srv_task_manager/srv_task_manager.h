#ifndef SRV_TASK_MANAGER_H
#define SRV_TASK_MANAGER_H

#define BUTTON_T1_REC_MS 10
#define SYNC_T2_REC_MS 50
#define ASYNC_T3_REC_MS 200

#define LED_1_ON_TIME_MS 1000
#define LED_2_ON_TIME_MS 300
#define LED_2_OFF_TIME_MS 500
#define BLINK_T4_ON_TIME_MS 100
#define BLINK_T4_OFF_TIME_MS 100
#define BLINK_T4_REC_MS 5000


#define BUTTON_TASK_STACK_SIZE 128
#define SYNC_TASK_STACK_SIZE 128
#define ASYNC_TASK_STACK_SIZE 128
#define TASK_PRIORITY 1

void buttonT1(void *pvParameters);
void syncT2(void *pvParameters);
void asyncT3(void *pvParameters);
void blinkT4(void *pvParameters);

#endif
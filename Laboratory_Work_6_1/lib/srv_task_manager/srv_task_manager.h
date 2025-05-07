#ifndef SRV_TASK_MANAGER_H
#define SRV_TASK_MANAGER_H

#define LED_CONTROL_TASK_REC_MS 100
#define SERIAL_REPORT_TASK_REC_MS 1000

#define SERIAL_REPORT_TASK_STACK_SIZE 256
#define LED_CONTROL_TASK_STACK_SIZE 256
#define TASK_PRIORITY 1

void ledControlTask(void *pvParameters);
void serialReportTask(void* pvParameters);

#endif
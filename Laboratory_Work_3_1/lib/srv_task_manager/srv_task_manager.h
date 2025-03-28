#ifndef SRV_TASK_MANAGER_H
#define SRV_TASK_MANAGER_H

#define JOYSTICK_TASK_REC_MS 100
#define SERIAL_REPORT_TASK_REC_MS 500

#define JOYSTICK_TASK_STACK_SIZE 128
#define SERIAL_REPORT_TASK_STACK_SIZE 128
#define TASK_PRIORITY 1

void joystickTask(void* pvParameters);
void serialReportTask(void* pvParameters);

#endif
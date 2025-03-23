#ifndef SRV_TASK_MANAGER_H
#define SRV_TASK_MANAGER_H

#define JOYSTICK_TASK_REC_MS 100
#define POTENTIOMETER_TASK_REC_MS 100
#define SERIAL_REPORT_TASK_REC_MS 1000

#define JOYSTICK_TASK_STACK_SIZE 256
#define POTENTIOMETER_TASK_STACK_SIZE 256
#define SERIAL_REPORT_TASK_STACK_SIZE 256
#define TASK_PRIORITY 1

void joystickTask(void* pvParameters);
void potentiometerTask(void* pvParameters);
void serialReportTask(void* pvParameters);

#endif
#ifndef SRV_TASK_MANAGER_H
#define SRV_TASK_MANAGER_H

#define COMMAND_HANDLER_TASK_REC_MS 200
#define MOTOR_CONTROL_TASK_REC_MS 100
#define SERIAL_REPORT_TASK_REC_MS 200

#define COMMAND_HANDLER_TASK_STACK_SIZE 256
#define SERIAL_REPORT_TASK_STACK_SIZE 256
#define MOTOR_CONTROL_TASK_STACK_SIZE 256
#define TASK_PRIORITY 1

void commandHandlerTask(void* pvParameters);
void motorUpdateTask(void *pvParameters);
void serialReportTask(void* pvParameters);

#endif
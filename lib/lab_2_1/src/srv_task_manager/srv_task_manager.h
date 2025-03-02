#ifndef SRV_TASK_MANAGER_H
#define SRV_TASK_MANAGER_H

#define BLINKING_LED_TASK_REC 0    // Run every 0ms (default)

void taskButtonLed();
void taskBlinkingLed();
void taskCounterButtons();
void taskIdle();

#endif
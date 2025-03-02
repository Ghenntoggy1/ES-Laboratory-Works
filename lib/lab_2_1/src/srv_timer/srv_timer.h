#ifndef SRV_TIMER_H
#define SRV_TIMER_H

// Include necessary libraries here

// Define any constants or macros here
#define SYS_TICK 1 // 1 milliseconds

// Task Recurrence Intervals (in ticks)
#define BUTTON_LED_TASK_REC 100    // Run every 10ms
#define BLINKING_LED_TASK_REC 0    // Run every 0ms (default)
#define COUNTER_BUTTONS_TASK_REC 1 // Run every 10ms
#define IDLE_TASK_REC 500          // Run every 1000ms

// Task Counters
int buttonLedTaskCounter = BUTTON_LED_TASK_REC;
int blinkingLedTaskCounter = BLINKING_LED_TASK_REC;
int counterButtonsTaskCounter = COUNTER_BUTTONS_TASK_REC;
int idleTaskCounter = IDLE_TASK_REC;

// Task States

// Declare any function prototypes here
void setupTimer1();
void timeScheduler();

#endif
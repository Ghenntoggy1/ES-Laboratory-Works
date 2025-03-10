#include "srv_timer.h"
#include "../srv_global_states/srv_global_states.h"
#include "../srv_task_manager/srv_task_manager.h"
#include <Arduino.h>

// Define the task counters
int buttonLedTaskCounter = BUTTON_LED_TASK_REC;
int blinkingLedTaskCounter = BLINKING_LED_TASK_REC;
int counterButtonsTaskCounter = COUNTER_BUTTONS_TASK_REC;
int idleTaskCounter = IDLE_TASK_REC;

void setupTimer1()
{
    noInterrupts(); // Disable interrupts during setup

    // Reset Timer1 control registers
    TCCR1A = 0;
    TCCR1B = 0;

    // Set CTC mode (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    // Set prescaler to 64
    TCCR1B |= (1 << CS11) | (1 << CS10);

    // Set compare match value for 1ms interval
    OCR1A = 249;
    
    // Enable Timer1 compare match interrupt
    TIMSK1 |= (1 << OCIE1A);

    interrupts(); // Re-enable interrupts
}

// Scheduler Function
void timeScheduler()
{
    // Dynamic recurrence for blinking LED task
    int dynamicBlinkingLedTaskRec = BLINKING_LED_TASK_REC + (lab_2_1_getCounter() * 100);

    // Task 1: Button LED
    if (--buttonLedTaskCounter <= 0)
    {
        buttonLedTaskCounter = BUTTON_LED_TASK_REC;
        taskButtonLed();
    }

    // Task 2: Blinking LED
    if (--blinkingLedTaskCounter <= 0)
    {
        blinkingLedTaskCounter = dynamicBlinkingLedTaskRec;
        taskBlinkingLed();
    }

    // Task 3: Counter Buttons
    if (--counterButtonsTaskCounter <= 0)
    {
        counterButtonsTaskCounter = COUNTER_BUTTONS_TASK_REC;
        taskCounterButtons();
    }
}

// Timer1 ISR for system tick
ISR(TIMER1_COMPA_vect)
{
    timeScheduler(); // Increment the system tick counter
}
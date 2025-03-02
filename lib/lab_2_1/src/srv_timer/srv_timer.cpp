#include "srv_timer.h"
#include "srv_global_states/srv_global_states.h"
#include "srv_task_manager/srv_task_manager.h"
#include <Arduino.h>

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

    // Set compare match value for 10ms interval
    OCR1A = 2499; // 16MHz / 64 / 2500 = 100Hz (10ms)

    // Enable Timer1 compare match interrupt
    TIMSK1 |= (1 << OCIE1A);

    interrupts(); // Re-enable interrupts
}

// Scheduler Function
void timeScheduler()
{
    // Dynamic recurrence for blinking LED task
    int dynamicBlinkingLedTaskRec = BLINKING_LED_TASK_REC + (getCounter() * 100);

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

    // Idle Task: Reporting
    if (--idleTaskCounter <= 0)
    {
        idleTaskCounter = IDLE_TASK_REC;
        taskIdle();
    }
}

// Timer1 ISR for system tick
ISR(TIMER1_COMPA_vect)
{
    timeScheduler(); // Increment the system tick counter
}
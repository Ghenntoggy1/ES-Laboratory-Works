#include "srv_task_manager.h"
#include "dd_button/dd_button.h"
#include "dd_led/dd_led.h"
#include "srv_global_states/srv_global_states.h"
#include <Arduino.h>

// Custom Components
Led led1(3);       // LED for Task 1
Led led2(4);       // LED for Task 2
Button button1(2); // Button for Task 1
Button button3(5); // Button for Task 3 (Decrement)
Button button2(6); // Button for Task 3 (Increment)

// Task Functions
void taskButtonLed()
{
    if (button1.isPressed())
    { // Button is pressed (active-low)
        setLed1State(!getLed1State());
        if (getLed1State())
        {
            led1.on(); // Turn on LED1
        }
        else
        {
            led1.off(); // Turn off LED1
        }

        // Force LED2 off when LED1 activates
        if (getLed1State())
        {
            led2.off(); // Turn off LED2
            setLed2State(LOW);
        }
    }
}

void taskBlinkingLed()
{
    if (!getLed1State())
    {
        setLed2State(!getLed2State());
        if (getLed2State())
        {
            led2.on(); // Turn on LED2
        }
        else
        {
            led2.off(); // Turn off LED2
        }
    }
    else
    {
        led2.off(); // Ensure LED2 is off when LED1 is on
    }
}

void taskCounterButtons()
{
    static bool button2Pressed = false; // Track if Button2 is pressed
    static bool button3Pressed = false; // Track if Button3 is pressed

    // Handle Increment (Button2)
    if (button2.isPressed())
    { // Use Button class
        if (!button2Pressed)
        {                                   // Only increment once per press
            // counter = min(counter + 1, 20); 
            setCounter(min(getCounter() + 1, 20)); // Increment by 1, max 20
            button2Pressed = true;          // Mark button as pressed
            printf("Increment!");           // Debug message
        }
    }
    else
    {
        button2Pressed = false; // Reset when button is released
    }

    // Handle Decrement (Button3)
    if (button3.isPressed())
    { // Use Button class
        if (!button3Pressed)
        {                                  // Only decrement once per press
            // counter = max(counter - 1, 1); 
            setCounter(max(getCounter() - 1, 1)); // Decrement by 1, min 1
            button3Pressed = true;         // Mark button as pressed
            printf("Decrement!\n");        // Debug message
        }
    }
    else
    {
        button3Pressed = false; // Reset when button is released
    }
}

void taskIdle()
{
    printf("LED1: ");
    printf(led1.getState() ? "ON\n" : "OFF\n");
    printf("LED2: ");
    printf(led2.getState() ? "ON\n" : "OFF\n");
    printf("Flash Interval: ");
    printf("%d", BLINKING_LED_TASK_REC + (getCounter() * 100)); // Convert ticks to ms
    printf(" ms\n");
    printf("Counter: ");
    printf("%d\n", getCounter());
    printf("------------------\n");
}
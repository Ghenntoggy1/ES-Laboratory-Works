#include "lab_2_1_main.h"
#include "dd_button/dd_button.h"
#include "dd_led/dd_led.h"
#include "srv_serial_stdio/srv_serial_stdio.h"
#include "srv_timer/srv_timer.h"
#include "srv_global_states/srv_global_states.h"
#include "srv_task_manager/srv_task_manager.h"
#include <Arduino.h>



void lab_2_1_setup()
{
    srvSerialSetup(); // Initialize serial I/O

    globalStatesSetup();  // Initialize global states

    setupTimer1(); // Set up Timer1 for system tick
}

void lab_2_1_loop()
{
    timeScheduler(); // Run the scheduler
    delay(SYS_TICK); // Maintain system tick interval
}
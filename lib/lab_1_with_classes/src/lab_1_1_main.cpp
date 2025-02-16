#include "lab_1_1_main.h"
#include "srv_serial_stdio/srv_serial_stdio.h"
#include "dd_led/dd_led.h"
#include <Arduino.h>

Led led(LED_BUILTIN);

void lab_1_1_setup() {
    srvSerialSetup();
    printf("Serial communication initialized!\n");
    printf("Enter 'ledon' to turn the LED on or 'ledoff' to turn it off.\n");
}

void lab_1_1_loop() {
    char c[11] = "";
    scanf("%10s", c);
    
    if (strcmp(c, "ledon") == 0) {
        led.on();
      	printf("Led was Turned On\n");
    } else if (strcmp(c, "ledoff") == 0) {
        led.off();
        printf("Led was Turned Off\n");
    } else {
    	delay(500);
    }
}
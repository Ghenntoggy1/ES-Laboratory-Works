#include "srv_serial_stdio.h"
#include <Arduino.h>
#include <stdio.h>

void srvSerialSetup() {
    Serial.begin(9600);

    static FILE serial_out;
    fdev_setup_stream(&serial_out, srvSerialPutChar, NULL, _FDEV_SETUP_WRITE);
    stdout = &serial_out;
    
    static FILE serial_in;
    fdev_setup_stream(&serial_in, NULL, srvSerialGetChar, _FDEV_SETUP_READ);
    stdin = &serial_in;
}

int srvSerialGetChar(FILE* stream) {
    if (Serial.available()) {
        return Serial.read();
    }
    return EOF;
}
int srvSerialPutChar(char c, FILE* stream) {
    Serial.write(c);
    return 0;
}
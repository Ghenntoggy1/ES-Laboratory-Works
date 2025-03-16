#ifndef SRV_SERIAL_STDIO_H
#define SRV_SERIAL_STDIO_H

// Include necessary libraries here
#include <stdio.h>

// Define any constants or macros here

// Declare any function prototypes here
void srvSerialSetup();
int srvSerialGetChar(FILE* stream);
int srvSerialPutChar(char c, FILE* stream);

#endif
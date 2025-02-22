#ifndef SRV_KEYPAD_STDIO_H
#define SRV_KEYPAD_STDIO_H

// Include necessary libraries here
#include <stdio.h>
#include <Arduino.h>
#include <Keypad.h>

// Define any constants or macros here
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

extern byte ROW_PINS[KEYPAD_ROWS];
extern byte COL_PINS[KEYPAD_COLS];
extern char KEYPAD_KEY[KEYPAD_ROWS][KEYPAD_COLS];

extern Keypad keypad;

// Declare any function prototypes here
void srvKeypadSetup();
int srvKeypadGetChar(FILE* stream);

#endif
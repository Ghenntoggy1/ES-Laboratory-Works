#ifndef SRV_LCD_STDIO_H
#define SRV_LCD_STDIO_H

// Include necessary libraries here
#include <stdio.h>

// Define any constants or macros here
#define LCD_ADDRESS 0x27
#define LCD_ROWS 2
#define LCD_COLS 16

// Declare any function prototypes here
void srvLCDSetup();
int srvLCDPutChar(char c, FILE* stream);
void srvLCDInit();
void srvLCDClear();
void srvLCDCursor(uint8_t col, uint8_t row);

#endif
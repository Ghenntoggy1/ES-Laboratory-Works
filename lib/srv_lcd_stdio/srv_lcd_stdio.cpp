#include "srv_lcd_stdio.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <stdio.h>

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

void srvLCDSetup() {    
    static FILE lcd_out;
    fdev_setup_stream(&lcd_out, srvLCDPutChar, NULL, _FDEV_SETUP_WRITE);
    stdout = &lcd_out;
}

int srvLCDPutChar(char c, FILE* stream) {
    lcd.print(c);
    return 0;
}

void srvLCDInit() {
    lcd.init();
    lcd.backlight();
    // lcd.begin(16, 2);

    printf("SETUP PIN:");
    lcd.setCursor(0, 1);
}

void srvLCDClear() {
    lcd.clear();
}

void srvLCDCursor(uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
}

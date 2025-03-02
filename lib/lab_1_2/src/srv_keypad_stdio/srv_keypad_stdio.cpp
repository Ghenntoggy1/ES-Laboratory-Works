#include "srv_keypad_stdio.h"
#include <Arduino.h>
#include <Keypad.h>
#include <stdio.h>

byte ROW_PINS[KEYPAD_ROWS] = {9, 8, 7, 6};
byte COL_PINS[KEYPAD_COLS] = {5, 4, 3, 2};

char KEYPAD_KEYS[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad keypad = Keypad(makeKeymap(KEYPAD_KEYS), ROW_PINS, COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

void srvKeypadSetup() {
    static FILE keypad_in;
    fdev_setup_stream(&keypad_in, NULL, srvKeypadGetChar, _FDEV_SETUP_READ);
    stdin = &keypad_in;
}

int srvKeypadGetChar(FILE* stream) {
    return keypad.getKey();
}

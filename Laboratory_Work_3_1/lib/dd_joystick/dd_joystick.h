#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "dd_button.h"

class Joystick {
    private:
        int xPin;
        int yPin;
        int xValue;
        int yValue;
        Button *button;
    
    public:
        Joystick(int xPin, int yPin, int buttonPin);
        int getX();
        int getY();
        bool getButtonState();
    };

#endif
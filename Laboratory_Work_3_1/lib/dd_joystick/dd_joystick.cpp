#include "dd_joystick.h"
#include <Arduino.h>

Joystick::Joystick(int xPin, int yPin, int buttonPin)
{
    this->xPin = xPin;
    this->yPin = yPin;
    this->xValue = 0;
    this->yValue = 0;
    this->button = new Button(buttonPin);
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
}

int Joystick::getX()
{
    int rawX = analogRead(xPin);
    this->xValue = map(rawX, 0, 1023, -512, 512);
    return this->xValue;
}

int Joystick::getY()
{
    int rawY = analogRead(yPin);
    this->yValue = map(rawY, 0, 1023, 512, -512);
    return this->yValue;
}

bool Joystick::getButtonState()
{
    return button->isPressed();
}

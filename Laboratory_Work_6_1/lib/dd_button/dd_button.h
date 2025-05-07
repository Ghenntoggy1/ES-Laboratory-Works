#ifndef BUTTON_H
#define BUTTON_H

class Button {
private:
    int buttonPin;
    int buttonState;

public:
    Button(int buttonPin);
    int readInput();
};

#endif
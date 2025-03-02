#ifndef BUTTON_H
#define BUTTON_H

class Button {
private:
    int buttonPin;

public:
    Button(int buttonPin);
    bool isPressed();
};

#endif
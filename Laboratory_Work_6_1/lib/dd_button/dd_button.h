#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_DEBOUNCE_TIME_MS 50


class Button {
private:
    int buttonPin;

public:
    Button(int buttonPin);
    bool isPressed();
};

#endif
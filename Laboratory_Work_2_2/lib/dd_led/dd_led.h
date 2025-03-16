#ifndef LED_H
#define LED_H

class Led {
private:
    int ledPin;

public:
    Led(int ledPin);
    int getState();
    void on();
    void off();
    void toggle();
};

#endif
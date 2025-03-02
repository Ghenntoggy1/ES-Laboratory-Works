#ifndef LED_H
#define LED_H

class Led {
private:
    int ledPin;

public:
    Led(int ledPin);
    void on();
    void off();
    int getState();
    void toggle();
};

#endif
#ifndef DD_RELAY_H
#define DD_RELAY_H

#include <Arduino.h>

class Relay {
private:
    int relayPin;
    bool state;
public:
    Relay(int pin);
    void init();
    void on();
    void off();
    bool isOn();
};

#endif
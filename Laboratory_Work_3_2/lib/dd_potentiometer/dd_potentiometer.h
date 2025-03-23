#ifndef DD_POTENTIOMETER_H
#define DD_POTENTIOMETER_H

class Potentiometer {
    private:
        int pin;
        int potValue;
    
    public:
        Potentiometer(int pin);
        int getPotValue();
};

#endif
#ifndef DD_ULTRASONIC_H
#define DD_ULTRASONIC_H

class DD_ULTRASONIC {
private:
    int trg_pin;
    int echo_pin;
    float distance;
    float hysteresisBand;
    float targetSetpoint;

public:
    DD_ULTRASONIC(int trg_pin, int echo_pin);
    void init();
    
    float getDistance();
    float getHysteresisBand();
    float getSetpoint();

    void setHysteresisBand(float hysteresisBand);
    void setTargetSetpoint(float targetSetpoint);
};

#endif
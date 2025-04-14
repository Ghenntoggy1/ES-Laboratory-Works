#ifndef DD_L298_H
#define DD_L298_H

class DD_L298 {
private:
    int channelAEnPin;
    int channelAIn1Pin;
    int channelAIn2Pin;

    int channelBEnPin;
    int channelBIn3Pin;
    int channelBIn4Pin;

    int saturate(int value, int min, int max);
public:
    DD_L298(int channelAEnPin = -1, int channelAIn1Pin = -1, int channelAIn2Pin = -1,
            int channelBEnPin = -1, int channelBIn3Pin = -1, int channelBIn4Pin = -1);
    void init();
    void set_pwm_motor_a(int speed);
    void set_pwm_motor_b(int speed);
    void stop_motor_a();
    void stop_motor_b();
    void stop_all_motors();
};

#endif
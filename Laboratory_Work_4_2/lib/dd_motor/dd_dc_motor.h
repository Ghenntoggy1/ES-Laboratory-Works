#ifndef DD_DC_MOTOR_H
#define DD_DC_MOTOR_H

#include <Arduino.h>
#include <dd_l298.h>

enum MotorChannel { MOTOR_A, MOTOR_B };
enum MotorDirection { FORWARD, STOPPED, BACKWARD };

class DCMotor {
private:
    DD_L298 *motorDriver;
    MotorChannel channel;
    int motorPower;
    int motorDirection;
    int saturate(int value, int min, int max);
    String convertEnumNameToString(MotorDirection direction);

public:
    DCMotor(DD_L298 *motorDriver, MotorChannel channel);
    void init();
    void set_power(int power);
    void stop_motor();
    int get_power();
    String is_going_forward();
};

#endif
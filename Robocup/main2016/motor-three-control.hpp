#ifndef MOTOR_FOR_ROBOT_H
#define MOTOR_FOR_ROBOT_H

#include "mbed.h"
#include "motor.hpp"

class MotorControl {
public:
    MotorControl(Motor motor1_, Motor motor2_, Motor motor3_);
    void turn();
    void move(float power, float moveAngle, float omega);
    void move(float power, float moveAngle, float omega);
    void changeDir(float curAngle ,float trgAngle);

private:
    Motor motor1;
    Motor motor2;
    Motor motor3;
};

MotorControl::MotorControl(Motor motor1_, Motor motor2_, Motor motor3_) :
    motor1(motor1_), motor2(motor2_), motor3(motor3_) {
}

MotorControl::

#endif /* MOTOR_FOR_ROBOT_H */
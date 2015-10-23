/**
 * @file   : motor-three-wheeler.h (1.0)
 * @brief  : motors for robot
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/23
 */

#ifndef MOTOR_FOR_ROBOT_H
#define MOTOR_FOR_ROBOT_H

#include "mbed.h"
#include "motor.hpp"

class MotorThreeWheeler {
public:
    MotorThreeWheeler(Motor motor1_, Motor motor2_, Motor motor3_);
    void turnClockwise();
    void turnCounterclockwise();
    void goStraight();
    void goBack();
    void goRight();
    void goLeft();
    void run();

private:
    Motor motor1;
    Motor motor2;
    Motor motor3;
};

MotorThreeWheeler::MotorThreeWheeler(Motor motor1_, Motor motor2_, Motor motor3_) :
    motor1(motor1_), motor2(motor2_), motor3(motor3_) {
}

#endif /* MOTOR_FOR_ROBOT_H */

/**
 * @file   : motor-three-wheeler.h (1.0)
 * @brief  : motors for robot
 * @author : Yohei SAITO(, Shinnosuke KOIKE)
 * @date   : 2015/10/30
 */

#ifndef MOTOR_FOR_ROBOT_H
#define MOTOR_FOR_ROBOT_H

#include "mbed.h"
#include "motor.hpp"

#define M_PI 3.14159265358979323846

class MotorThreeWheeler {
public:
    MotorThreeWheeler(Motor motor1_, Motor motor2_, Motor motor3_);
    void brake(void);
    void turn(float power);
    void go_straight(float power);
    void go_back(float power);
    void go_right(float power);
    void go_left(float power);
    void run(float power, float angle);

private:
    Motor motor1;
    Motor motor2;
    Motor motor3;
};

MotorThreeWheeler::MotorThreeWheeler(Motor motor1_, Motor motor2_, Motor motor3_) :
    motor1(motor1_), motor2(motor2_), motor3(motor3_) {
}

void MotorThreeWheeler::brake(){
    motor1.brake();
    motor2.brake();
    motor3.brake();
}

void MotorThreeWheeler::turn(float power){
    motor1.run(power);
    motor2.run(power);
    motor3.run(power);
}

void MotorThreeWheeler::run(float power, float angle){
    while (angle > (2 * M_PI)) {
        angle -= (2 * M_PI);
    }

    double component_x = 0.7559 * cos(angle);
    double component_y = 0.6546 * sin(angle);

    motor1.run(power * ( component_x - component_y));
    motor2.run(power * (-component_x - component_y));
    motor3.run(power * component_y);
}

void MotorThreeWheeler::go_straight(float power){
    power *= 0.7559;
    motor1.run( power);
    motor2.run(-power);
    motor3.run(0);
}

void MotorThreeWheeler::go_back(float power){
    power *= 0.7559;
    motor1.run(-power);
    motor2.run(power);
    motor3.run(0);
}

void MotorThreeWheeler::go_right(float power){
    power *= 0.6546;
    motor1.run(-power);
    motor2.run(-power);
    motor2.run( power);
}

void MotorThreeWheeler::go_left(float power){
    power *= 0.6546;
    motor1.run( power);
    motor2.run( power);
    motor2.run(-power);
}

#endif /* MOTOR_FOR_ROBOT_H */

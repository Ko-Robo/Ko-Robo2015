#ifndef MOTOR_FOR_ROBOT_H
#define MOTOR_FOR_ROBOT_H

#include "mbed.h"
#include "motor.hpp"

class MotorFourWheeler {
public:
    MotorFourWheeler(Motor motor1_, Motor motor2_, Motor motor3_, Motor motor4_);
    void setLimit(float powerLimit1 = 1, float powerLimit2 = 1, float powerLimit3 = 1, float powerLimit4 = 1);
    void turn(float allPower);
    void run(float power1, float power2, float power3, float power4);

private:
    Motor motor1;
    Motor motor2;
    Motor motor3;
    Motor motor4;
};

MotorFourWheeler::MotorFourWheeler(Motor motor1_, Motor motor2_, Motor motor3_, Motor motor4_) :
    motor1(motor1_), motor2(motor2_), motor3(motor3_), motor4(motor4_) {
}

void MotorFourWheeler::setLimit(float powerLimit1, float powerLimit2, float powerLimit3, float powerLimit4) {
    motor1.setLimit(powerLimit1);
    motor2.setLimit(powerLimit2);
    motor3.setLimit(powerLimit3);
    motor4.setLimit(powerLimit4);
}

void MotorFourWheeler::turn(float allPower) {
    motor1.run(allPower);
    motor2.run(allPower);
    motor3.run(allPower);
    motor4.run(allPower);
}

void MotorFourWheeler::run(float power1, float power2, float power3, float power4) {
    motor1.run(power1);
    motor2.run(power2);
    motor3.run(power3);
    motor4.run(power4);
}

#endif /* MOTOR_FOR_ROBOT_H */
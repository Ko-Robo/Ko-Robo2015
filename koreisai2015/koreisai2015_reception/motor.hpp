/**
 * @file   : motor.h (1.0)
 * @brief  : control moter
 * @author : Yohei SAITO(, Shinnosuke KOIKE)
 * @date   : 2015/08/04
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "mbed.h"

class Motor {
public:
    Motor();
    Motor(PinName normalDirect, PinName reverseDirect, PinName pwm);
    ~Motor();
    int  setLimit(float powerLimit = 1);
    void setFlequency(float correctFlequency);
    void run(float power); // input -1 ~ 1
    void brake(void);
    void operator=(float power);

private:
    float limit;
    PwmOut* powerLevel;
    DigitalOut normal;
    DigitalOut reverse;
    void rotateNormal(void);
    void rotateReverse(void);
};

// initialize
Motor::Motor(PinName normalDirect, PinName reverseDirect, PinName pwm):
    normal(normalDirect), reverse(reverseDirect) {
    powerLevel = new PwmOut(pwm);
    limit = 1;
}

Motor::~Motor() {
    delete powerLevel;
}

// set flequency
void Motor::setFlequency(float correctFlequency) {
    powerLevel->period(1 / correctFlequency);
}

// set power limit
int Motor::setLimit(float powerLimit) {
    if (powerLimit > 1 || powerLimit < -1) return 1;

    limit = powerLimit;
    return 0;
}

// run moter
void Motor::run(float power) {
    if (power > 1)  power = 1;
    if (power < -1) power = -1;
    if (power < 0) {
        powerLevel->write(-power * limit);
        rotateReverse();
    } else {
        powerLevel->write(power * limit);
        rotateNormal();
    }
}

void Motor::operator=(float power){
    this->run(power);
}

// rotate in the clockwise
void Motor::rotateNormal(void) {
    normal  = 1;
    reverse = 0;
}

// rotate in the anticlockwise
void Motor::rotateReverse(void) {
    normal  = 0;
    reverse = 1;
}

// brake
void Motor::brake(void) {
    normal  = 1;
    reverse = 1;
    powerLevel->write(limit);
}

<<<<<<< HEAD:Robocup/main2016/motor.hpp
#endif

/*
 * example program

#include "mbed.h"
#include "motor.h"

int main(void) {
    Motor motor(D4, D7, D9);
    motor.setLimit(0.8);
    while (1) {
        motor.run(-0.2);    // D4->Low   D7->High  D9(duty) = 0.2 * 0.8 = 0.16
        motor.run(2);       // D4->High  D7->Low   D9(duty) = 1.0 * 0.8 = 0.8
        motor = 0.5;       // same as run(0.5);
    }
}
 */
 
=======
#endif /* MOTOR_H */
>>>>>>> baseFork/master:koreisai2015/koreisai2015_reception/motor.hpp

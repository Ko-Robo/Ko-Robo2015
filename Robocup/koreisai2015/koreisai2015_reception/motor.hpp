/**
 * @file   : motor.h (1.0)
 * @brief  : control moter
 * @author : Yohei SAITO(, Shinnosuke KOIKE)
 * @date   : 2015/08/18
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "mbed.h"

class Motor {
public:
    Motor(PinName normalDirect, PinName reverseDirect, PinName pwm);
    ~Motor();
    bool setLimit(float powerLimit = 1);
    void setFlequency(float correctFlequency);
    void run(float power);
    void brake(void);

private:
    // power level of motor
    PwmOut* powerLevel;
    // forward direction of motor
    DigitalOut normal;
    // reverse direction of motor
    DigitalOut reverse;
    //! motor's power limit
    float limit;
    void rotateNormal(void);
    void rotateReverse(void);
};

/**
 * @fn
 * @breaf : initialize normal, reverse and powerLevel instance
 * @param : (normalDirect) normal rotation
 * @param : (reverseDirect) reverse rotation
 * @param : (pwm) pwm for motor
 */
Motor::Motor(PinName normalDirect, PinName reverseDirect, PinName pwm):
    normal(normalDirect), reverse(reverseDirect) {
    powerLevel = new PwmOut(pwm);
    this->limit = 1;
}

/**
 * @fn
 * @breaf : release memory of powerLevel
 */
Motor::~Motor() {
    delete powerLevel;
}

/**
 * @fn
 * @breaf : set frequency
 * @param : (correctFrequency) frequency for communicating
 */
void Motor::setFlequency(float correctFlequency) {
    powerLevel->period(1 / correctFlequency);
}

/**
 * @fn
 * @breaf : set power limit
 * @param : (powerLimit) speed of rotation
 * @return : if it is successful, return 0, if not return 1
 */
bool Motor::setLimit(float powerLimit) {
    if (powerLimit > 1 || powerLimit < -1) return false;

    limit = powerLimit;
    return true;
}

/**
 * @fn
 * @breaf : run motor
 * @param : (power) speed of lotation
 */
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

/**
 * @fn
 * @breaf : rotate in the clockwise
 */
void Motor::rotateNormal(void) {
    normal  = 1;
    reverse = 0;
}

/**
 * @fn
 * @breaf : rotate in the anticlockwise
 */
void Motor::rotateReverse(void) {
    normal  = 0;
    reverse = 1;
}

/**
 * @fn
 * @breaf : brake
 */
void Motor::brake(void) {
    normal  = 1;
    reverse = 1;
    powerLevel->write(limit);
}

#endif

/*
 * example program

#include "mbed.h"
#include "motor.h"

int main(void) {
    Motor motor(D4, D7, D9);
    motor.setLimit(0.8);
    while (1) {
        motor.run(-0.2);    // Then D4->Low   D7->High  D9(duty) = 0.2 * 0.8 = 0.16
        motor.run(2);       // Then D4->High  D7->Low   D9(duty) = 1.0 * 0.8 = 0.8
    }
}
 */

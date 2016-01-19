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
    Motor(PinName normal_direct, PinName reverse_direct, PinName pwm);
    int  set_limit(float power_limit = 1);
    void set_frequency(float correct_frequency);
    void run(float power); // input -1 ~ 1
    void brake(float powor = 1);
    void operator =(float power);

private:
    float limit;
    PwmOut* power_level;
    DigitalOut normal;
    DigitalOut reverse;
    void rotate_normal(void);
    void rotate_reverse(void);
};

// initialize
Motor::Motor(PinName normal_direct, PinName reverse_direct, PinName pwm):
    normal(normal_direct), reverse(reverse_direct) {
    power_level = new PwmOut(pwm);
    limit = 1;
}

// set flequency
void Motor::set_frequency(float correct_frequency) {
    power_level->period(1 / correct_frequency);
}

// set power limit
int Motor::set_limit(float power_limit) {
    if (power_limit > 1 || power_limit < -1) return 1;

    limit = power_limit;
    return 0;
}

// run moter
void Motor::run(float power) {
    if (power > 1)  power = 1;
    if (power < -1) power = -1;
    if (power < 0) {
        power_level->write(-power * limit);
        rotate_reverse();
    } else {
        power_level->write(power * limit);
        rotate_normal();
    }
}

void Motor::operator=(float power){
    run(power);
}

// rotate in the clockwise
void Motor::rotate_normal(void) {
    normal  = 1;
    reverse = 0;
}

// rotate in the anticlockwise
void Motor::rotate_reverse(void) {
    normal  = 0;
    reverse = 1;
}

// brake
void Motor::brake(float powor) {
    normal  = 1;
    reverse = 1;
    power_level->write(powor * limit);
}

#endif /* MOTOR_H */

/*
 * example program
#include "mbed.h"
#include "motor.h"
int main(void) {
    Motor motor(D4, D7, D9);
    motor.set_limit(0.8);
    while (1) {
        motor.run(-0.2);    // D4->Low   D7->High  D9(duty) = 0.2 * 0.8 = 0.16
        motor.run(2);       // D4->High  D7->Low   D9(duty) = 1.0 * 0.8 = 0.8
        motor = 0.5;       // same as run(0.5);
    }
}
 */

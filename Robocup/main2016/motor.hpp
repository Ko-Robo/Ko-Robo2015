/**
 * @file   : motor.h (1.0)
 * @brief  : control moter
 * @author : Yohei SAITO(, Shinnosuke KOIKE)
 * @date   : 2015/10/23
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "mbed.h"

class Motor {
public:
    Motor(PinName normal_direct, PinName reverse_direct, PinName pwm);
    bool set_limit(float power_limit = 1);
    void set_frequency(float correct_frequency);
    void run(float power);
    void brake(void);

private:
    PwmOut* power_level;
    DigitalOut normal;
    DigitalOut reverse;
    float limit;
    void rotate_normal(void);
    void rotate_reverse(void);
};

Motor::Motor(PinName normal_direct, PinName reverse_direct, PinName pwm):
    normal(normal_direct), reverse(reverse_direct) {
    power_level = new PwmOut(pwm);
}

void Motor::set_frequency(float correct_frequency) {
    power_level->period(1 / correct_frequency);
}

bool Motor::set_limit(float power_limit) {
    if (power_limit > 1 || power_limit < -1) return false;

    limit = power_limit;
    return true;
}

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

void Motor::rotate_normal(void) {
    normal  = 1;
    reverse = 0;
}

void Motor::rotate_reverse(void) {
    normal  = 0;
    reverse = 1;
}

void Motor::brake(void) {
    normal  = 1;
    reverse = 1;
    power_level->write(limit);
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
        motor.run(-0.2);    // Then D4->Low   D7->High  D9(duty) = 0.2 * 0.8 = 0.16
        motor.run(2);       // Then D4->High  D7->Low   D9(duty) = 1.0 * 0.8 = 0.8
    }
}
 */

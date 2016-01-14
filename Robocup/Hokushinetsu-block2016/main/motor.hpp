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

protected:
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
    limit = 0.8;
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

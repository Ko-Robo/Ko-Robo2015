/**
 * @file   : dribbler.h (1.0)
 * @brief  : dribble the ball
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/23
 */

#ifndef DRIBBLER_H
#define DRIBBLER_H

#include "mbed.h"
#include "motor.hpp"

class Dribbler {
public:
    Dribbler(PinName normal_direct, PinName reverse_direct, PinName pwm, PinName dribbler_IR_);
    void dribble(float power);

private:
    DigitalIn dribbler_IR;
    Motor dribbler_motor;
};

Dribbler::Dribbler(PinName normal_direct, PinName reverse_direct, PinName pwm, PinName dribbler_IR_) :
        dribbler_IR(dribbler_IR_), dribbler_motor(normal_direct, reverse_direct, pwm) {
    dribbler_motor.set_limit(0.8);
}

void Dribbler::dribble(float power) {
    if (dribbler_IR == 0) {
        dribbler_motor.run(power);
    } else {
        dribbler_motor.brake();
    }
}

#endif /* DRIBBLER_H */

/**
 * example program

#include "mbed.h"
#include "dribbler.h"

int main(void) {
    Dribbler dribbler(D4, D7, D9, D0);
    while (1) {
        dribbler.dribble(0.2);
    }
}
 */

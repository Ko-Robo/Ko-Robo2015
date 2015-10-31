#ifndef DRIBBLER_H
#define DRIBBLER_H

#include "mbed.h"
#include "motor.hpp"

class Dribbler : Motor {
public:
    Dribbler(PinName normal_direct, PinName reverse_direct, PinName pwm);
    void run();
};

Dribbler::Dribbler(PinName normal_direct, PinName reverse_direct, PinName pwm) : Motor(normal_direct, reverse_direct, pwm) {
}

void Dribbler::run() {
    power_level->write(limit);
    rotate_normal();
}

#endif /* DRIBBLER_H */

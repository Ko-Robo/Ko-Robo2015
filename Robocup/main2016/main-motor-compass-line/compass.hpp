/**
 * @file   : compass.h (1.0)
 * @brief  : measure angle
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/24
 */

#ifndef COMPASS_H
#define COMPASS_H

#include "mbed.h"
#include "HMC6352.h"

class Compass {
public:
    Compass(HMC6352 hmc6352_);
    float measure_angle(void);

private:
    // digital compass module
    HMC6352* hmc6352;
    float initial_angle;
};

Compass::Compass(HMC6352 hmc6352_) {
    hmc6352 = new HMC6352(hmc6352_);
    hmc6352->setOpMode(HMC6352_CONTINUOUS, 1, 20);
    wait(0.05);
    initial_angle = hmc6352->sample() / 10.0;
}

float Compass::measure_angle(void) {
    float diff_angle = hmc6352->sample() / 10.0 - initial_angle;
    return diff_angle;
}

#endif /* COMPASS_H */

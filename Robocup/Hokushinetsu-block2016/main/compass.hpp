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
    Compass(PinName sda, PinName scl);
    float measure_angle();
    float measure_angle(float compare_angle);

private:
    // digital compass module
    HMC6352* hmc6352;
    float initial_angle;
    float get_correct_angle(float difference_angle);
};

Compass::Compass(PinName sda, PinName scl) {
    hmc6352 = new HMC6352(sda, scl);
    hmc6352->setOpMode(HMC6352_CONTINUOUS, 1, 20);
    do {
        initial_angle = hmc6352->sample() / 10.0;
    } while (initial_angle >= 360 || initial_angle < 0);
}

float Compass::get_correct_angle(float difference_angle) {
    if (difference_angle < -180)     return difference_angle + 360;
    else if (difference_angle > 180) return difference_angle - 360;
    else                             return difference_angle;
}

float Compass::measure_angle() {
    float difference_angle = hmc6352->sample() / 10.0 - initial_angle;
    return get_correct_angle(difference_angle);
}

float Compass::measure_angle(float compare_angle) {
    float difference_angle = hmc6352->sample() / 10.0 - compare_angle;
    return get_correct_angle(difference_angle);
}

#endif /* COMPASS_H */

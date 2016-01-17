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
    float measure_angle(void);

private:
    // digital compass module
    HMC6352* hmc6352;
    float initial_angle;
};

Compass::Compass(PinName sda, PinName scl) {
    hmc6352 = new HMC6352(sda, scl);
    hmc6352->setOpMode(HMC6352_CONTINUOUS, 1, 20);

    do{
        initial_angle = hmc6352->sample() / 10.0;
    } while(initial_angle >= 360 || initial_angle <0 );

}

float Compass::measure_angle(void) {
    float hmc = hmc6352->sample() / 10.0;

    if(hmc - inital_angle < -180){
        return hmc - inital_angle + 360;
    }else if(hmc - inital_angle > 180){
        return hmc - inital_angle - 360;
    }else{
        return hmc - inital_angle;
    }

}

#endif /* COMPASS_H */

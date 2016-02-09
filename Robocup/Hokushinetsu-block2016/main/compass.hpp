/**
 * @file   : compass.h (1.0)
 * @brief  : measure angle
 * @author : Shinnosuke KOIKE, Yohei SAITO
 * @date   : 2015/2/9
 */

#ifndef COMPASS_H
#define COMPASS_H

#include "mbed.h"
#include "HMC6352.h"

#define ENTER_CAL_MODE true
#define EXIT_CAL_MODE  false

class Compass {
public:
    Compass(PinName sda, PinName scl);
    void  init();
    float measure_angle();
    float measure_angle(float compare_angle);
    float read_raw_angle();
    void  set_calibration(bool mode);
    float get_initial_angle();

private:
    static float initial_angle;
    // digital compass module
    HMC6352* hmc6352;
    float get_correct_angle(float difference_angle);
    bool is_calibration_mode;
};

float Compass::initial_angle = 0;

Compass::Compass(PinName sda, PinName scl) {
    hmc6352 = new HMC6352(sda, scl);
    hmc6352->setOpMode(HMC6352_CONTINUOUS, 1, 20);
}

void Compass::init(){
    hmc6352->setOpMode(HMC6352_CONTINUOUS, 1, 20);
    float sum = 0;
    for (float cnt = 0; cnt < 10; cnt++) {
        if (initial_angle >= 360 || initial_angle < 0) continue;
        sum += hmc6352->sample() / 10.0;
    }
    initial_angle = sum / 10;
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

float Compass::read_raw_angle() {
    return hmc6352->sample() / 10.0;
}

void Compass::set_calibration(bool mode){
    if (mode == ENTER_CAL_MODE && is_calibration_mode != mode) {
        hmc6352->setCalibrationMode(0x43);
        is_calibration_mode = !is_calibration_mode;
    }
    if (mode == EXIT_CAL_MODE && is_calibration_mode != mode) {
        hmc6352->setCalibrationMode(0x45);
        is_calibration_mode = !is_calibration_mode;
    }
}

float Compass::get_initial_angle() {
    return initial_angle;
}

#endif /* COMPASS_H */

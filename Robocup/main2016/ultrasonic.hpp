/**
 * @file   : ultrasonic.h (1.0)
 * @brief  : measure distance from something
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/23
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "mbed.h"
#include "hcsr04.h"

class Ultrasonic {
public:
    Ultrasonic(HCSR04 hcsr04_);
    int measure_dist(void);

private:
    // ultrasonic distance sensor
    HCSR04* hcsr04;
};

Ultrasonic::Ultrasonic(HCSR04 hcsr04_) {
    hcsr04 = new HCSR04(hcsr04_);
}

int Ultrasonic::measure_dist(void) {
    int dist = hcsr04->distance();
    return dist;
}

#endif /* ULTRASONIC_H */

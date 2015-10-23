/**
 * @file   : ultrasonic.h (1.0)
 * @brief  : measure distance from something
 * @author : Shinnosuke KOIKE
 * @date   : 2015/08/18
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

/**
 * example program

#include "mbed.h"
#include "ultrasonic.h"

HCSR04 hcsr04(D12, D13);

int main(void) {
    Ultrasonic ultrasonic(hcsr04);
    while (1) {
        pc.printf("%d\r\n", ultrasonic.measure_dist());
    }
}
 */

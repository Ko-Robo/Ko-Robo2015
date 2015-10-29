#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "mbed.h"
#include "hcsr04.h"

class Ultrasonic {
public:
    Ultrasonic(PinName trig, PinName echo);
    long measure_distance(void);

private:
    // ultrasonic sensor
    HCSR04* hcsr04
    long distance;
};

Ultrasonic::Ultrasonic(PinName trig, PinName echo) {
    hcsr04 = new HCSR04(trig, echo);
}

long Ultrasonic::measure_distance(void) {
    wait(0.1);
    distance = hcsr04->distance();
    if (distance > 100) return -1;
    return distance;
}

#endif /* ULTRASONIC_H */

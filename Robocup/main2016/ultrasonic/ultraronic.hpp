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
    HCSR04* hcsr04;
};

Ultrasonic::Ultrasonic(PinName trig, PinName echo) {
    hcsr04 = new HCSR04(trig, echo);
}

long Ultrasonic::measure_distance(void) {
    return hcsr04->distance();
}

#endif /* ULTRASONIC_H */

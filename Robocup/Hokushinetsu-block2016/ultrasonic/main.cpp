#include "mbed.h"
#include "ultrasonic.hpp"
#include "i2cslave-support.hpp"

#define ADDRESS 0xF0

Ultrasonic* ultrasonics[4] = {
    new Ultrasonic(D1, D0), // front
    new Ultrasonic(D2, D3), // right
    new Ultrasonic(D6, D7), // back
    new Ultrasonic(D8, D9)  // left
};

I2CSlaveSupport communication(D4, D5);

char distances[4];

inline void measure_distance(unsigned int sensor_direction) {
    sensor_direction %= 4;
    distances[sensor_direction] = ultrasonics[sensor_direction]->measure_distance();
}

int main(void) {
    for (int i = 0; ; i++) {
        measure_distance(i);
        communication.do_i2c(ADDRESS, distances, 4, communication.WRITE);
    }
}

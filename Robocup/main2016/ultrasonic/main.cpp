#include "mbed.h"
#include "ultrasonic.hpp"

Ultrasonic ultrasonic_1(dp1, dp2);
Ultrasonic ultrasonic_2(dp4, dp6);
Ultrasonic ultrasonic_3(dp9, dp10);

I2CSlave communication(dp5, dp27);

int main(void) {
    char distances[3];
    communication.address(0xF0);
    while (1) {
        distances[0] = ultrasonic_1.measure_distance();
        distances[1] = ultrasonic_2.measure_distance();
        distances[2] = ultrasonic_3.measure_distance();

        communication.write(distances, 1);
    }
}

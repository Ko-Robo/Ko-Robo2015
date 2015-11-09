#include "mbed.h"
#include "ultrasonic.hpp"

Ultrasonic ultrasonic_front(dp1, dp2);
Ultrasonic ultrasonic_right(dp4, dp6);
Ultrasonic ultrasonic_back(dp9, dp10);
Ultrasonic ultrasonic_left(dp11, dp13);

I2CSlave i2c(dp5, dp27);

char return_each_distance(int sensor_pos) {
    unsigned char distance;
    switch (sensor_pos) {
        case 0:
            distance = ultrasonic_front.measure_distance();
            break;
        case 1:
            distance = ultrasonic_right.measure_distance();
            break;
        case 2:
            distance = ultrasonic_back.measure_distance();
            break;
        case 3:
            distance = ultrasonic_left.measure_distance();
            break;
    }

    return distance;
}

int main(void) {
    char distances[4];
    unsigned int sensor_pos = 0;
    i2c.address(0xF0);
    while (1) {
        int reception_check = i2c.receive();
        switch (reception_check) {
            case I2CSlave::ReadAddressed:
                i2c.write(distances, 4);
                i2c.stop();
                break;
            case I2CSlave::WriteGeneral:
                // 全マイコンに受信要求された時の処理
                break;
            case I2CSlave::WriteAddressed:
                // このマイコンに受信要求された時の処理
                break;
            case I2CSlave::NoData:
            default:
                distances[sensor_pos % 4] = return_each_distance(sensor_pos % 4);
                sensor_pos++;
                break;
        }
    }
}

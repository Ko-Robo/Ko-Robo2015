#include "mbed.h"
#include "ultrasonic.hpp"

Ultrasonic ultrasonic_front(dp1, dp2);
Ultrasonic ultrasonic_right(dp4, dp6);
Ultrasonic ultrasonic_back(dp9, dp10);
Ultrasonic ultrasonic_left(dp11, dp13);
Ultrasonic ultrasonics[4] = {ultrasonic_front, ultrasonic_right, ultrasonic_back, ultrasonic_left};

I2CSlave i2c(dp5, dp27);

int main(void) {
    char distances[4];
    unsigned int sensor_direction = 0;
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
                distances[sensor_direction % 4] = ultrasonics[sensor_direction % 4].measure_distance();
                sensor_direction++;
                break;
        }
    }
}

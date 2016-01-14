#include "mbed.h"
#include "ultrasonic.hpp"

Ultrasonic* ultrasonics[4] = {
    new Ultrasonic(D1, D0), // front
    new Ultrasonic(D2, D3), // right
    new Ultrasonic(D6, D7), // back
    new Ultrasonic(D8, D9)  // left
};

I2CSlave i2c(D4, D5);

char distances[4];

inline void measure_distance(unsigned int sensor_direction) {
    sensor_direction %= 4;
    distances[sensor_direction] = ultrasonics[sensor_direction]->measure_distance();
}

int main(void) {
    i2c.address(0xF0);

    for (int i = 0; ; i++) {
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
                measure_distance(i);
                break;
        }
    }
}

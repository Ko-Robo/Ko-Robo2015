#include "mbed.h"
#include "ultrasonic.hpp"

Ultrasonic* ultrasonics[4] = {
    new Ultrasonic(dp1, dp2),  // front
    new Ultrasonic(dp4, dp6),  // right
    new Ultrasonic(dp9, dp10), // back
    new Ultrasonic(dp11, dp13) // left
};

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
                distances[sensor_direction % 4] = ultrasonics[sensor_direction % 4]->measure_distance();
                sensor_direction++;
                break;
        }
    }
}

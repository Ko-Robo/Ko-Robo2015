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

<<<<<<< HEAD:Robocup/main2016/ultrasonic/main.cpp
void measure_distance(void const* args) {
    const unsigned int sensor_direction = (const char*)args;
    while (1) {
        distances[(const char*)args] = ultrasonics[(const char*)args]->measure_distance();
    }
}


int main(void) {
    i2c.address(0xF0);
    Thread thread0(measure_distance,(void*)0);
    Thread thread1(measure_distance,(void*)1);
    Thread thread2(measure_distance,(void*)2);
    Thread thread3(measure_distance,(void*)3);
=======
inline void measure_distance(unsigned int sensor_direction) {
    sensor_direction %= 4;
    distances[sensor_direction] = ultrasonics[sensor_direction]->measure_distance();
}

int main(void) {
    i2c.address(0xF0);
>>>>>>> FETCH_HEAD:Robocup/Hokushinetsu-block2016/ultrasonic/main.cpp

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

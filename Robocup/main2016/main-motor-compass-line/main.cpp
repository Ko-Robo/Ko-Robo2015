/**
 * @file   : main.cpp (0.1)
 * @brief  : oversee all
 * @author : Shinnosuke KOIKE
 * @date   : 2015/07/17
 */

#include "mbed.h"
#include "motor.hpp"
#include "motor-three-wheeler.hpp"
#include "compass.hpp"
#include "PID.h"

Motor motor1(p15, p16, p23);
Motor motor2(p17, p18, p22);
Motor motor3(p19, p20, p21);

BusIn lines(p24, p25, p26, p29);

I2C top(p9, p10);
I2C bottom(p28, p27);
Compass compass(p9, p10);

DigitalIn ball(p11);
DigitalOut kick(p12);

InterruptIn alert(p30);

int main(void) {
    while (1) {

    }
}

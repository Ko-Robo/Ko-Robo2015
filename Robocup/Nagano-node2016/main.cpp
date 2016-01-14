#include "mbed.h"
#include "motor.hpp"
#include "kicker.hpp"

Motor motor1(p20, p19, p21);
Motor motor2(p15, p17, p24);
Motor motor3(p26, p27, p25);

Kicker kicker(LED1, p8);

DigitalIn infrared(p8);

DigitalIn line(p7);

Ticker timer;

DigitalOut led(LED1);

void move(double powor, double moveAngle) {
    double cosine = cos(moveAngle * 0.0174533);
    double sine   = sin(moveAngle * 0.0174533);

    motor1 = powor * (0.35 * sine - 0.6062177826491071 * cosine);
    motor2 = powor * (-0.70 * sine);
    motor3 = powor * (0.35 * sine + 0.6062177826491071 * cosine);
}

void to_field() {
    if (line) {
        led = 1;
        timer.detach();
        move(0.3, 180);
        wait(2);
        timer.attach_us(&to_field, 100);
    } else {
        led = 0;
    }
}

int main(void) {
    motor1.setLimit(0.3);
    motor2.setLimit(0.3);
    motor3.setLimit(0.3);
    timer.attach_us(&to_field, 50);
    kicker.enable_kick();

    while(1) {
        if (infrared) {
            move(0.6, 0);
        } else {
            motor1.brake();
            motor2.brake();
            motor3.brake();
        }
    }
}

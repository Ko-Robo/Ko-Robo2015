#include "mbed.h"
#include "kicker.hpp"
#include "motor.hpp"

Motor dribbler(dp26, dp25, dp24);
Kicker kicker(dp9, dp10);

DigitalOut info_of_holding_ball(dp1);

DigitalIn holding_ball(dp2);
InterruptIn kick_order(dp4);

void kick(void) {
    dribbler.run(0);
    wait_ms(10);
    kicker.kick();
}

int main(void) {
    kick_order.rise(&kick);
    while (1) {
        if (holding_ball) {
            dribbler.run(0.35);
            info_of_holding_ball = 1;
        } else {
            dribbler.run(0);
            info_of_holding_ball = 0;
        }
    }
}

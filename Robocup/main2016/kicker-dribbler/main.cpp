#include "mbed.h"
#include "kicker.hpp"
#include "dribbler.hpp"

Dribbler dribbler(dp26, dp25, dp24);
Kicker kicker(dp9, dp10);

DigitalOut kick(dp1);

InterruptIn hold(dp2);
InterruptIn kick_order(dp4);

int main(void) {
    kick_order.rise(&kicker, &Kicker::kick);
    hold.fall(&dribbler, &Dribbler::run);
    while (1) {

    }
}

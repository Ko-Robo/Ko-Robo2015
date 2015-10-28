#include "mbed.h"
#include "kicker.hpp"
#include "motor.hpp"

Motor dribbler(dp26, dp25, dp24);
Kicker kicker(dp9, dp10);

DigitalOut kick(dp1);
DigitalIn hold(dp2);

int main(void) {
    while (1) {

    }
}

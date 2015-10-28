#include "mbed.h"
#include "limit.hpp"
#include "seven-segment-LED.hpp"

BusOut anode(dp1, dp2, dp4, dp6, dp9, dp10, dp11, dp13);
BusOut cathode(dp15, dp16, dp17, dp18);

PwmOut buzzer(dp24);
DigitalIn button(dp25);

I2C communication(dp5, dp27);
DigitalOut to_main(dp26);

int main(void) {
    while (1) {

    }
}

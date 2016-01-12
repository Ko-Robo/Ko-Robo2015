#include "mbed.h"

DigitalOut sw_led2(dp1);
DigitalOut led2(dp2);
DigitalOut sw_led(dp13);
DigitalOut led(dp13);

BusOut leds(dp14, dp28, dp15, dp26);

BusIn rotary_sw(dp24, dp18, dp17, dp25);

I2CSlave communication(dp5, dp27);

int main(void) {
    communication.address(0x32);
    while (1) {

    }
}

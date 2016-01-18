#include "mbed.h"
#include "i2cslave-support.hpp"

DigitalIn  start_stop_sw(dp11);
DigitalOut start_stop_sw_led(dp13);
DigitalIn  sw(dp2);
DigitalOut sw_led(dp1);

BusOut leds(dp14, dp28, dp15, dp26);
BusIn rotary_sw(dp24, dp18, dp17, dp25);

I2CSlaveSupport communication(dp5, dp27);

#define ADDRESS 0x32

bool check_start_stop_sw() {
    char sw_val[3];
    if (start_stop_sw) {
        while (start_stop_sw) {
            sw_val[0] = false;
            sw_val[1] = sw;
            sw_val[2] = rotary_sw ^ 0xf;
            communication.do_i2c(ADDRESS, sw_val, 3, communication.WRITE);
        }
        return true;
    }
    return false;
}

int main(void) {
    char sw_val[3];
    bool is_transmitted;

    while (1) {
        is_transmitted = false;
        sw_val[0] = (char)check_start_stop_sw();
        sw_val[1] = sw;
        sw_val[2] = rotary_sw ^ 0x0f;
        while (!is_transmitted) {
            is_transmitted = communication.do_i2c(ADDRESS, sw_val, 3, communication.WRITE);
        }
    }
}

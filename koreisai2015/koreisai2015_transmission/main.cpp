#include "mbed.h"

Serial xbee(dp16, dp15);
AnalogIn left_to_right(dp9);
AnalogIn up_to_down(dp10);
BusIn buttons(dp4, dp5, dp6);
BusOut leds(dp14,dp17,dp28);
PwmOut pwm(dp18);
int main(void) {
    xbee.format(8, Serial::None, 1);

    while (1) {
        xbee.putc(0);
        wait_ms(15);
        pwm = 1;
        unsigned short buttons_data = buttons;
        xbee.putc(buttons_data);
        leds = buttons;
        wait_ms(15);

        pwm = 0.9;
        unsigned short up_to_down_data = up_to_down.read_u16();
        unsigned short upper_eight_bits = up_to_down_data >> 8;
        xbee.putc(upper_eight_bits);
        wait_ms(15);

        pwm = 0.8;
        unsigned short lower_eight_bits = up_to_down_data;
        xbee.putc(lower_eight_bits);
        wait_ms(15);

        pwm = 0.7;
        unsigned short left_to_right_data = left_to_right.read_u16();
        upper_eight_bits = left_to_right_data >> 8;
        xbee.putc(upper_eight_bits);
        wait_ms(15);

        pwm = 0.8;
        lower_eight_bits = left_to_right_data;
        xbee.putc(lower_eight_bits);
        wait_ms(15);

        pwm = 0.9;
    }
}

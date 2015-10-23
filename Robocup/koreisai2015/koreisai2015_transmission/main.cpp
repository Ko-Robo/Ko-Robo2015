#include "mbed.h"

Serial xbee(dp16, dp15);
AnalogIn leftToRight(dp9);
AnalogIn upToDown(dp10);
BusIn buttons(dp4, dp5, dp6);
BusOut leds(dp14,dp17,dp28);
PwmOut pwm(dp18);
int main(void) {
    xbee.format(8, Serial::None, 1);

    while (1) {
        xbee.putc(0);
        wait_ms(15);   
        pwm = 1;
        unsigned short buttonsData = buttons;
        xbee.putc(buttonsData);
        leds = buttons;
        wait_ms(15);

        pwm = 0.9;
        unsigned short upToDownData = upToDown.read_u16();
        unsigned short upperEightBits = upToDownData >> 8;
        xbee.putc(upperEightBits);
        wait_ms(15);

        pwm = 0.8;
        unsigned short lowerEightBits = upToDownData;
        xbee.putc(lowerEightBits);
        wait_ms(15);

        pwm = 0.7;
        unsigned short leftToRightData = leftToRight.read_u16();
        upperEightBits = leftToRightData >> 8;
        xbee.putc(upperEightBits);
        wait_ms(15);

        pwm = 0.8;
        lowerEightBits = leftToRightData;
        xbee.putc(lowerEightBits);
        wait_ms(15);

        pwm = 0.9;
    }
}

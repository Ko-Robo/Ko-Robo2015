#include "mbed.h"
#define SHORT_MAX 65536.0

Serial xbee(dp16, dp15);
AnalogIn leftToRight(dp9);
AnalogIn upToDown(dp10);
BusIn buttons(dp1, dp2, dp25);//L R SW
BusOut LEDs( dp14, dp17, dp28);//ボタンデータを反映
PwmOut pwmLed( dp18);//テキトーに光らせる

int main(void) {
    xbee.format(8, Serial::None, 1);

    while (1) {
        pwmLed = 0.1;
        xbee.putc(0x0);
        wait_ms(15);

        pwmLed = 0.4;
        unsigned short buttonsData = buttons;
        xbee.putc(~buttonsData);
        LEDs = ~buttonsData;
        wait_ms(15);

        pwmLed = 0.8;
        unsigned short upToDownData = upToDown.read_u16();
        unsigned short upperEightBits = upToDownData >> 8;
        xbee.putc(upperEightBits);
        wait_ms(15);
       
        pwmLed = 1;
        unsigned short lowerEightBits = upToDownData;
        xbee.putc(lowerEightBits);
        wait_ms(15);
        
        pwmLed = 0.6;
        unsigned short leftToRightData = leftToRight.read_u16();
        upperEightBits = leftToRightData >> 8;
        xbee.putc(upperEightBits);
        wait_ms(15);
        
        pwmLed = 0.2;
        lowerEightBits = leftToRightData;
        xbee.putc(lowerEightBits);
        wait_ms(15);
    }
}

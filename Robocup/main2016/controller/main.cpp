#include "mbed.h"

DigitalOut sw_led2(dp1);
DigitalOut led2(dp2);
DigitalOut sw_led(dp13);
DigitalOut led(dp13);

BusOut leds(dp14, dp28, dp15, dp26);

BusIn rotary_sw(dp24, dp18, dp17, dp25);

I2CSlave communication(dp5, dp27);

int main(void) {
    int rotary_sw_val;
    communication.address(0x32);
    while (1) {
        rotary_sw_val = rotary_sw ^ 0xf;
        int reception_check = communication.receive();
        switch (reception_check) {
            case I2CSlave::ReadAddressed:
                communication.write(rotary_sw_val);
                communication.stop();
                break;
            case I2CSlave::WriteGeneral:
                // 全マイコンに受信要求された時の処理
                break;
            case I2CSlave::WriteAddressed:
                // このマイコンに受信要求された時の処理
                break;
            case I2CSlave::NoData:
                break;
            default:
                break;
        }
    }
}

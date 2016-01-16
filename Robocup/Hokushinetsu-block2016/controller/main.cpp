#include "mbed.h"

DigitalOut start_stop_sw(dp1);
DigitalOut start_stop_sw_led(dp2);
DigitalOut sw_led(dp13);
DigitalOut led(dp13);

BusOut leds(dp14, dp28, dp15, dp26);

BusIn rotary_sw(dp24, dp18, dp17, dp25);

I2CSlave communication(dp5, dp27);

bool check_start_stop_sw() {
    if (start_stop_sw) {
        while (start_stop_sw)
            ;
        return true;
    }
    return false;
}

int main(void) {
    char sw_val[2];

    communication.address(0x32);
    while (1) {
        sw_val[0] = (char)check_start_stop_sw();
        sw_val[1] = rotary_sw ^ 0xf;

        int reception_check = communication.receive();
        switch (reception_check) {
            case I2CSlave::ReadAddressed:
                communication.write(sw_val, 1);
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

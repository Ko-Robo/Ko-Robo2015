#include "mbed.h"

DigitalOut start_stop_sw(dp2);
DigitalOut start_stop_sw_led(dp1);
DigitalOut sw(dp13);
DigitalOut sw_led(dp14);
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
    char sw_values[3];
    char data[4];
    bool is_transmit;

    communication.address(0x32);

    while (1) {
        is_transmit = false;
        sw_values[0] = (char)check_start_stop_sw();
        sw_values[1] = rotary_sw ^ 0xf;
        sw_values[2] = sw;

        while (!is_transmit) {
            int reception_check = communication.receive();
            switch (reception_check) {
                case I2CSlave::ReadAddressed:
                    communication.write(sw_values, 1);
                    communication.stop();
                    is_transmit = true;
                    break;
                case I2CSlave::WriteGeneral:
                    communication.read(data, 4);
                    communication.stop();
                    break;
                case I2CSlave::WriteAddressed:
                    communication.read(data, 4);
                    communication.stop();
                    break;
                case I2CSlave::NoData:
                    break;
                default:
                    break;
            }
        }
    }
}

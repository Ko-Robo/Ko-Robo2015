#include "mbed.h"

DigitalIn  start_stop_sw(dp2);
DigitalOut start_stop_sw_led(dp1);
DigitalIn  white_sw(dp11);
DigitalOut white_sw_led(dp13);

BusOut leds(dp14, dp28, dp15, dp26);
BusIn rotary_sw(dp24, dp18, dp17, dp25);

I2CSlave communication(dp5, dp27);

enum I2C_Status { NoData, WRITE, READ_General, READ};

int i2c(I2CSlave *i2c_slave, char *data_array, int data_length, char behave = 0){

    int reception_check = i2c_slave->receive();

    if( (behave)&&(reception_check != behave)) return false;

    switch (reception_check){
                    case I2CSlave::ReadAddressed:
                    i2c_slave->write(data_array, length);
                    i2c_slave->stop();
                break;
            case I2CSlave::WriteGeneral:
                    i2c_slave->read(data_array, data_length);
                    i2c_slave->stop();
                break;
            case I2CSlave::WriteAddressed:
                    i2c_slave->read(data_array, data_length);
                    i2c_slave->stop();
                break;
            case I2CSlave::NoData:
            default:
                break;
        }
    return true;
}

bool check_start_stop_sw() {
    char sw_val[3];
    if (start_stop_sw) {
        while(start_stop_sw){
            sw_val[0] = false;
            sw_val[1] = white_sw;
            sw_val[2] = rotary_sw ^ 0xf;
            i2c( &communication, sw_val, 3, WRITE);
        }
        start_stop_sw_led = sw_val[0];
        white_sw_led      = sw_val[1];
        return true;
    }
    return false;
}

int main(void) {
    char sw_val[3];
    int i2c_state;

    communication.address(0x32);

    while (1) {

        sw_val[0] = check_start_stop_sw();

        do{
            sw_val[1] = white_sw;
            sw_val[2] = rotary_sw ^ 0x0f;
            i2c_state = i2c( &communication,  sw_val, 3, WRITE);
        }while( !i2c_state);

        start_stop_sw_led = sw_val[0];
        white_sw_led      = sw_val[1];
    }
}
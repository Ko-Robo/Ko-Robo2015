#include "mbed.h"

BusIn infrared(dp1, dp2, dp4, dp6, dp9, dp10, dp11, dp13, dp15, dp16, dp17, dp18);
BusIn far(dp24, dp25);

I2CSlave i2c(dp5, dp27);

char exchange(long near_data, char far_data) {
    int angle = 0;
    char cnt = 0;
    char base;
    long judge = near_data | (near_data << 12);

    if (!near_data || (near_data == 0xfff))
        return far_data | 0xfc;

    //0が三つ連続である時を探す
    for (base = 11; ((judge >> base) & 7); base--);

    //三つ連続するところがないとき0を1つで考える
    if (base <= 0) {
        for (base = 11; ((near_data >> base) & 1); base--);
    }

    for (char i = base; i < (base + 12); i++) {
        if (((near_data >> (i % 12)) & 1)) {
            cnt++;
            angle += i;
        }
    }

    return (int)(angle * 21.0 / cnt) % 252;
}

int main(void) {
<<<<<<< HEAD
    communication.address(0xE0);
=======
    i2c.address(0xA0);
>>>>>>> 781a245aeaacc6347e494dd27e2c33219b305220
    while (1) {
        int reception_check = i2c.receive();
        switch (reception_check) {
            case I2CSlave::ReadAddressed:
                i2c.write( sendData, 1);
                i2c.stop();
                break;
            case I2CSlave::WriteGeneral:
                // 全マイコンに受信要求された時の処理
                break;
            case I2CSlave::WriteAddressed:
                // このマイコンに受信要求された時の処理
                break;
            case I2CSlave::NoData:
            default:
                sendData = exchange(infrared, far);
        	break;
        }
    }
}

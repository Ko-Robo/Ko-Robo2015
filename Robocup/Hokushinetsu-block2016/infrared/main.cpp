#include "mbed.h"
#include "i2cslave-support.hpp"

#define ADDRESS 0xA0

BusIn infrared(dp1, dp2, dp4, dp6, dp9, dp10, dp11, dp13, dp15, dp16, dp17, dp18);
BusIn far_infrared(dp24, dp25);

I2CSlaveSupport communication(dp5, dp27);

char get_correct_data(long near_data, char far_data) {
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
    char send_data;
    while (1) {
        send_data = get_correct_data(infrared, far_infrared);
        communication.do_i2c(ADDRESS, &send_data, 1, communication.WRITE);
    }
}

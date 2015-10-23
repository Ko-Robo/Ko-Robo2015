/**
 * @file   : infrared.h (1.0)
 * @brief  : examine point the ball exist
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/23
 */

#ifndef INFRARED_H
#define INFRARED_H

#include "mbed.h"

class Infrared {
public:
    Infrared(PinName front, PinName front_left, PinName left, PinName back_left,
        PinName back, PinName back_right, PinName right, PinName front_right);
    char find_ball_pos(void);

private:
    // infrared sensors
    BusIn infrared_data;
};

Infrared::Infrared(PinName front, PinName front_left, PinName left, PinName back_left,
        PinName back, PinName back_right, PinName right, PinName front_right):
    infrared_data(front, front_left, left, back_left, back, back_right, right, front_right) {
}

char Infrared::find_ball_pos(void) {
    char data = infrared_data;
    return data;
}

#endif /* INFRARED_H */

/**
 * example program(normal)

#include "mbed.h"
#include "infrared.h"

int main(void) {
    Infrared infrared(D0, D1, D2, D3, D4, D5, D6, D7);
    while (1) {
        char data = infrared.find_ball_pos();
        pc.printf("%d\r\n", data);  // for example, display "11000001"
    }
}
 */

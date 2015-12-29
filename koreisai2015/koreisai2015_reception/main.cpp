#include "mbed.h"
#include "motor.hpp"
#include "kicker.hpp"

#define HAFT_OF_MAX 32768.0

Serial pc(USBTX, USBRX);
Serial xbee(PA_11, PA_12);
Motor  motorA(PA_13, PA_14, PA_15);
Motor  motorB(PC_2, PC_3, PB_7);
Motor  motorC(PB_15, PB_14, PB_13);
Motor  motorD(PC_5, PC_8, PC_6);

char operation_data[6];

void receive(void) {
    static int i = 1;
    operation_data[i % 6] = xbee.getc();
    i++;
}

int main(void) {
    motorA.set_limit(0.3);
    motorB.set_limit(0.33);
    motorC.set_limit(0.3);
    motorD.set_limit(0.3);

    xbee.format(8, Serial::None, 1);
    while (xbee.getc());
    xbee.attach(&receive, Serial::RxIrq);

    while (1) {
        if (operation_data[1] & 0b01) {
            motorA.run(1);
            motorB.run(1);
            motorC.run(1);
            motorD.run(1);
        } else if (operation_data[1] & 0b10) {
            motorA.run(-1);
            motorB.run(-1);
            motorC.run(-1);
            motorD.run(-1);
        } else {
            unsigned short up_to_down    = (operation_data[2] << 8) | operation_data[3];
            unsigned short left_to_right = (operation_data[4] << 8) | operation_data[5];
            double up_to_down_coefficient = up_to_down / HAFT_OF_MAX - 1;
            double left_to_right_coefficient = left_to_right / HAFT_OF_MAX - 1;

            double powerA = up_to_down_coefficient *  0.7 + left_to_right_coefficient *  0.7;
            double powerB = up_to_down_coefficient *  0.7 + left_to_right_coefficient * -0.7;
            double powerC = up_to_down_coefficient * -0.7 + left_to_right_coefficient * -0.7;
            double powerD = up_to_down_coefficient * -0.7 + left_to_right_coefficient *  0.7;

            motorA.run(powerA);
            motorB.run(powerB);
            motorC.run(powerC);
            motorD.run(powerD);
        }
    }
}

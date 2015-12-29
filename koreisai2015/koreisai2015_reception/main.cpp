#include "mbed.h"
#include "motor.h"

#define harfOfMax 32768.0

Serial xbee(PA_11, PA_12);
Motor motorA(PA_13, PA_14, PA_15);
Motor motorB(PC_2, PC_3, PB_7);
Motor motorC(PB_15, PB_14, PB_13);
Motor motorD(PC_5, PC_8, PC_6);

char operationData[6];

void receive(void) {
    static int i = 1;
    operationData[i%6] = xbee.getc();
    i++;
}


int main(void) {
    motorA.setLimit(0.3);
    motorB.setLimit(0.33);
    motorC.setLimit(0.3);
    motorD.setLimit(0.3);

    xbee.format(8, Serial::None, 1);
    while (xbee.getc());
    xbee.attach(&receive, Serial::RxIrq);

    while (1) {
        if (!(operationData[1]&0b100==0b100)) {
            motorA.run(0.2);
            motorB.run(0.2);
            motorC.run(0.2);
            motorD.run(0.2);
        
          } else if (!(operationData[1]&0b001==0b001)) {
              motorA.run(-0.2);
              motorB.run(-0.2);
              motorC.run(-0.2);
              motorD.run(-0.2);

          } else {

            unsigned short upToDown    = (operationData[2] << 8) | operationData[3];
            unsigned short leftToRight = (operationData[4] << 8) | operationData[5];
            double upToDownCoefficient    = upToDown / harfOfMax - 1;
            double leftToRightCoefficient = leftToRight / harfOfMax - 1;

            double powerA = upToDownCoefficient *  0.5 + leftToRightCoefficient *  0.5;
            double powerB = upToDownCoefficient *  0.5 + leftToRightCoefficient * -0.5;
            double powerC = upToDownCoefficient * -0.5 + leftToRightCoefficient * -0.5;
            double powerD = upToDownCoefficient * -0.5 + leftToRightCoefficient *  0.5;

            if(operationData[1]&0b001){
                powerA *= 2;   
                powerB *= 2;   
                powerC *= 2;   
                powerD *= 2;   
            }

            motorA.run(powerA);
            motorB.run(powerB);
            motorC.run(powerC);
            motorD.run(powerD);
        }
    }
}
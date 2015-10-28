#include "mbed.h"

I2C communication(dp5, dp27);

int main(void) {
    communication.address(0x32);
    while (1) {

    }
}

#include "mbed.h"
#include "limit.hpp"
#include "seven-segment-LED.hpp"

SevenSegmentLED seven_segment(dp1, dp2, dp4, dp6, dp9, dp10, dp11, dp13, dp15, dp16, dp17, dp18);

PwmOut buzzer(dp24);
DigitalIn button(dp25);

I2C communication(dp5, dp27);
DigitalOut to_main(dp26);

int main(void) {
    seven_segment.enable_dynamic_lighting(2500);
    int val = 0;
    while (1) {
        seven_segment.display_data(val);
        val++;
    }
}

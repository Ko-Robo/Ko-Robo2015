/**
 * @file   : seven-segment-LED.h (1.0)
 * @brief  : light 7seg
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/29
 */

#ifndef SEVEN_SEGMENT_LED_H
#define SEVEN_SEGMENT_LED_H

#include "mbed.h"

class SevenSegmentLED {
public:
    SevenSegmentLED(PinName anode1, PinName anode2, PinName anode3,
                    PinName anode4, PinName anode5, PinName anode6,
                    PinName anode7, PinName anode8,
                    PinName cathode1, PinName cathode2,
                    PinName cathode3, PinName cathode4);
    void display_data(int value, int dot_point = 0);
    void enable_dynamic_lighting(int interval = 1000);
    void dynamic_lighting();

private:
    BusOut anode;
    BusOut cathode;
    Ticker timer;
    char data[4];
};

SevenSegmentLED::SevenSegmentLED(PinName anode1, PinName anode2, PinName anode3,
        PinName anode4, PinName anode5, PinName anode6, PinName anode7, PinName anode8,
        PinName cathode1, PinName cathode2, PinName cathode3, PinName cathode4) :
        anode(anode8, anode7, anode6, anode5, anode4, anode3, anode2, anode1),
        cathode(cathode1, cathode2, cathode3, cathode4) {
    for (int i = 0; i < 4; i++) {
        data[i] = 0;
    }
}

void SevenSegmentLED::enable_dynamic_lighting(int interval) {
    timer.attach_us(this, &SevenSegmentLED::dynamic_lighting, interval);
}

void SevenSegmentLED::display_data(int value, int dot_point) {
    for (int i = 3; i >= 0; value /= 10, i--) {
        switch (value % 10) {
            case 1:
                data[i] = 0b01100000; // 1
                break;
            case 2:
                data[i] = 0b11011010; // 2
                break;
            case 3:
                data[i] = 0b11110010; // 3
                break;
            case 4:
                data[i] = 0b01100110; // 4
                break;
            case 5:
                data[i] = 0b10110110; // 5
                break;
            case 6:
                data[i] = 0b10111110; // 6
                break;
            case 7:
                data[i] = 0b11100000; // 7
                break;
            case 8:
                data[i] = 0b11111110; // 8
                break;
            case 9:
                data[i] = 0b11110110; // 9
                break;
            case 0:
                data[i] = 0b11111100; // 0
                break;
            default:
                data[i] = 0b00000000; // non
                break;
        }
        if (3 - dot_point == i) {
            data[i] |= 1;
        }
    }
}

void SevenSegmentLED::dynamic_lighting() {
    static unsigned int shift_num = 0;
    cathode = ~(1 << shift_num);
    anode = data[shift_num];
    shift_num++;
    if (shift_num == 4) {
        shift_num = 0;
    }
}

#endif /* SEVEN_SEGMENT_LED_H */

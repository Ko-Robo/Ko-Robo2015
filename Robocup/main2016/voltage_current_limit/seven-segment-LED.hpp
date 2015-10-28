/**
 * @file   : seven-segment-LED.h (1.0)
 * @brief  : light 7seg
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/23
 */

#ifndef SEVEN_SEGMENT_LED_H
#define SEVEN_SEGMENT_LED_H

#include "mbed.h"

class SevenSegmentLED {
public:
    SevenSegmentLED(/* ピン名(BusOutで一度に指定??) */);
    light();

private:
    Ticker timer;
    char displaying_char[4];
};

#endif /* SEVEN_SEGMENT_LED_H */

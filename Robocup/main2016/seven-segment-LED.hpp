#ifndef SEVEN_SEGMENT_LED_H
#define SEVEN_SEGMENT_LED_H

#include "mbed.h"

class Seven_segment_LED {
public:
    Seven_segment_LED(/* ピン名(BusOutで一度に指定??) */);
    light();

private:
    Ticker timer;
    char displaying_char[4];
}
#endif /* SEVEN_SEGMENT_LED_H */
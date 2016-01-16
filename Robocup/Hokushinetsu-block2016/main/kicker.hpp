/**
 * @file   : kicker.h (1.0)
 * @brief  : kick the ball
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/24
 */

#ifndef KICKER_H
#define KICKER_H

#include "mbed.h"

class Kicker {
public:
    Kicker(PinName kicker_, PinName touch_ball_, int interval_ = 2);
    bool kick(void);

private:
    DigitalOut kicker;
    DigitalIn touch_ball;
    Timeout timer;
    const int interval;
    bool kicker_flag;
    void enable_kick();
};

Kicker::Kicker(PinName kicker_, PinName touch_ball_, int interval_):
        kicker(kicker_), touch_ball(touch_ball_), interval(interval_) {
    kicker_flag = true;
}

bool Kicker::kick(void) {
    if (touch_ball && kicker_flag) {
        kicker = 1;
        wait(0.001);
        kicker = 0;
        kicker_flag = false;
        timer.attach(this, &Kicker::enable_kick, interval);
        return true;
    }
    return false;
}

void Kicker::enable_kick() {
    kicker_flag = true;
}

#endif /* KICKER_H */

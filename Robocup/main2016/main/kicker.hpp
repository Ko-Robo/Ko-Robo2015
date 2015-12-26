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
    void enable_kick();
    void disable_kick();

private:
    DigitalOut kicker;
    DigitalIn touch_ball;
    Ticker timer;
    const int interval;
    void kick(void);
};

Kicker::Kicker(PinName kicker_, PinName touch_ball_, int interval_):
    kicker(kicker_), touch_ball(touch_ball_), interval(interval_) {
}

void Kicker::kick(void) {
    if (touch_ball) {
        kicker = 1;
        wait(0.001);
        kicker = 0;
    }
}

void Kicker::enable_kick() {
    timer.attach(this, &Kicker::kick, interval);
}

void Kicker::disable_kick() {
    timer.detach();
}

#endif /* KICKER_H */

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
    void kick(void);

private:
    DigitalOut kicker;
    DigitalIn touch_ball;
    Timer timer;
    const int interval;
    bool validate_kick(void);
};

Kicker::Kicker(PinName kicker_, PinName touch_ball_, int interval_):
    kicker(kicker_), touch_ball(touch_ball_), interval(interval_) {
    timer.start();
}

void Kicker::kick(void) {
    if (touch_ball && validate_kick()) {
        kicker = 1;
        wait(0.05);
        kicker = 0;
        timer.reset();
    }
}

inline bool Kicker::validate_kick() {
    return (timer.read() >= interval);
}

#endif /* KICKER_H */

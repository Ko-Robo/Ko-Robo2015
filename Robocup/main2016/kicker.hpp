/**
 * @file   : kicker.h (1.0)
 * @brief  : kick the ball
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/23
 */

#ifndef KICKER_H
#define KICKER_H

#include "mbed.h"

class Kicker {
public:
    Kicker(PinName kicker_, PinName touch_ball_, int interval_);
    ~Kicker();
    void kick(void);

private:
    DigitalOut kicker;
    DigitalIn touch_ball;
    Timer timer;
    const int interval;
    bool can_kick;
    void count(void);
};

Kicker::Kicker(PinName kicker_, PinName touch_ball_, int interval_):
    kicker(kicker_), touch_ball(touch_ball_), interval(interval_) {
    timer.start();
}

Kicker::~Kicker() {
    timer.reset();
    timer.stop();
}


void Kicker::kick(void) {
    this->count();
    if (touch_ball && can_kick) {
        kicker = 1;
        wait(0.05);
        this->can_kick = 0;
        kicker = 0;
        timer.reset();
    }
}

void Kicker::count(void) {
    float val = timer.read();
    if (val >= this->interval) {
        this->can_kick = 1;
    }
}

#endif /* KICKER_H */

/**
 * example program

#include "mbed.h"
#include "kicker.h"

int main(void) {
    const int interval = 2;
    Kicker kicker(D0, D1, interval);
    while (1) {
        kicker.kick();
    }
}
 */

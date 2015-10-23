/**
 * @file   : kicker.h (1.0)
 * @brief  : kick the ball
 * @author : Shinnosuke KOIKE
 * @date   : 2015/08/19
 */

#ifndef KICKER_H
#define KICKER_H

#include "mbed.h"

class Kicker {
public:
    Kicker(PinName kicker_, PinName touchBall_, int interval_);
    ~Kicker();
    void kick(void);

private:
    DigitalOut kicker;
    // ball contact sensor
    DigitalIn touchBall;
    Timer timer;
    const int interval;
    //! kick flag
    bool enableKick;
    void count(void);
};

/**
 * @fn
 * @breaf : initialize kicker and start timer
 * @param : (kicker_) kicker
 * @param : (touchBall_) find ball which exists before their's eyes
 * @param : (interval_) kick interval
 */
Kicker::Kicker(PinName kicker_, PinName touchBall_, int interval_):
    kicker(kicker_), touchBall(touchBall_), interval(interval_) {
    timer.start();
}

/**
 * @fn
 * @breaf : reset timer and stop
 */
Kicker::~Kicker() {
    timer.reset();
    timer.stop();
}

/**
 * @fn
 * @breaf : if ball exist before their's eyes and was set a kick flag, kick the ball
 */
void Kicker::kick(void) {
    this->count();
    if ((touchBall | 1) && enableKick) {
        kicker = 1;
        wait(0.05);
        this->enableKick = 0;
        kicker = 0;
        timer.reset();
    }
}

/**
 * @fn
 * @breaf : count interval seconds and set kick flag
 */
void Kicker::count(void) {
    float val = timer.read();
    if (val >= this->interval) {
        this->enableKick = 1;
    }
}

#endif

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
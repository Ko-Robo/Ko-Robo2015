#ifndef MICON_H
#define MICON_H

#include "mbed.h"
#include "micon-state.hpp"
#include "motor.hpp"
#include "compass.hpp"
#include "kicker.hpp"

#define CONTROLER_ADDRESS  0x32
#define IR_ADDRESS         0xA0
#define ULTRASONIC_ADDRESS 0xF0

class MiconBehavior;
class MotorControl;

enum MODE {NORMAL, KEEPER, LINE_TRACE, KAMIKAZE, DEBUG_COMPASS, DEBUG_LINE, DEBUG_KICKER, DEBUG_DRIBBLER, DEBUG_I2C};

class Micon {
public:
    static DigitalIn* lines[4];
    static I2C* i2c_top;
    static I2C* i2c_bottom;
    static PwmOut* sound;
    static Compass* compass;
    static Kicker* kicker;
    static Ticker* flipper_sw;
    static Ticker* flipper_line;
    static MotorControl* motors;

    static void behaves(char);
    static void init();

private:
    static void check_sw();
    static void check_start_stop_sw(char);
    static void chmod(char);
    static void check_line();

};

#include "micon-behavior.hpp"
#include "motor-control.hpp"

DigitalIn* Micon::lines[4] = {
    new DigitalIn(p5),
    new DigitalIn(p7),
    new DigitalIn(p8),
    new DigitalIn(p6)
};

Compass* Micon::compass        = new Compass(p9, p10);
MotorControl* Micon::motors = new MotorControl(p15, p16, p23, p17, p18, p22, p19, p20, p21, p9, p10, 10);
I2C*     Micon::i2c_top        = new I2C(p9, p10);
I2C*     Micon::i2c_bottom     = new I2C(p28, p27);
PwmOut*  Micon::sound          = new PwmOut(p24);
Kicker*  Micon::kicker         = new Kicker(p11, p30);
Ticker*  Micon::flipper_sw     = new Ticker();
Ticker*  Micon::flipper_line   = new Ticker();

void Micon::init() {
    flipper_sw->attach(&Micon::check_sw, 0.1);
    flipper_line->attach(&Micon::check_line, 0.01);
}

void Micon::behaves(char mode) {
    switch (mode) {
        case NORMAL:
            MiconBehavior::run_normal();
            break;
        case KEEPER:
            MiconBehavior::run_keeper();
            break;
        case LINE_TRACE:
            MiconBehavior::run_line_trace();
            break;
        case KAMIKAZE:
            MiconBehavior::run_kamikaze();
            break;
        case DEBUG_COMPASS:
            MiconBehavior::run_debug_compass();
            break;
        case DEBUG_LINE:
            MiconBehavior::run_debug_line();
            break;
        case DEBUG_KICKER:
            MiconBehavior::run_debug_kicker();
            break;
        case DEBUG_DRIBBLER:
            MiconBehavior::run_debug_dribbler();
            break;
        case DEBUG_I2C:
            MiconBehavior::run_debug_i2c();
            break;
        default:
            MiconBehavior::run_normal();
            break;
    }
}

void Micon::check_sw() {
    char sw_values[3];
    i2c_top->read(CONTROLER_ADDRESS | 1, sw_values, 3);

    check_start_stop_sw(sw_values[0]);
    chmod(sw_values[2]);
}

void Micon::check_start_stop_sw(char sw_val) {
    if (!sw_val) return;

    if (MiconState::is_running()) {
        MiconState::set_run_state(false);
    } else {
        MiconState::set_run_state(true);
    }
}

void Micon::chmod(char  mode_number) {
    MiconState::set_mode( mode_number);
}

void Micon::check_line() {
}


#endif /* MICON_H */

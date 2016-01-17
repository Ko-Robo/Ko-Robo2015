#ifndef MICON_H
#define MICON_H

#include "mbed.h"
#include "micon-state.hpp"
#include "micon-behavior.hpp"
#include "motor.hpp"
#include "compass.hpp"
#include "kicker.hpp"
#include "PID.h"

#define CONTROLER_ADDRESS  0x32
#define IR_ADDRESS         0xA0
#define ULTRASONIC_ADDRESS 0xF0

enum MODE {NORMAL, KEEPER, LINE_TRACE, KAMIKAZE, DEBUG_COMPASS, DEBUG_LINE, DEBUG_KICKER, DEBUG_DRIBBLER};

class Micon {
public:
    static Motor* motors[3];
    static BusIn* lines;
    static I2C* i2c_top;
    static I2C* i2c_bottom;
    static Compass* compass;
    static Kicker* kicker;
    static Ticker* flipper_sw;
    static Ticker* flipper_line;

    static void behaves(char);
    static void init();

private:
    Micon();
    static void check_sw();
    static void check_start_stop_sw(char);
    static void chmod(char);
    static void check_line();
};

Motor* Micon::motors[3] = {
    new Motor(p15, p16, p17),
    new Motor(p17, p18, p22),
    new Motor(p19, p20, p21)
};
BusIn*   Micon::lines          = new BusIn(p24, p25, p26, p29);
I2C*     Micon::i2c_top        = new I2C(p9, p10);
I2C*     Micon::i2c_bottom     = new I2C(p28, p27);
Compass* Micon::compass        = new Compass(p9, p10);
Kicker*  Micon::kicker         = new Kicker(p12, p11);
Ticker*  Micon::flipper_sw     = new Ticker();
Ticker*  Micon::flipper_line   = new Ticker();

void Micon::init() {
    flipper_sw->attach(&Micon::check_sw, 0.5);
    flipper_line->attach(&Micon::check_line, 0.5);
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
        default:
            MiconBehavior::run_normal();
            break;
    }
}

void Micon::check_sw() {
    char sw_values[2];
    i2c_top->read(CONTROLER_ADDRESS | 1, sw_values, 1);

    check_start_stop_sw(sw_values[0]);
    chmod(sw_values[1]);
}

void Micon::check_start_stop_sw(char sw_val) {
    if (!sw_val) return;

    if (MiconState::is_running()) {
        MiconState::set_run_state(false);
    } else {
        MiconState::set_run_state(true);
    }
}

void Micon::chmod(char sw_val) {
    if (sw_val > 7) {
        MiconState::set_mode(0);
    }
    MiconState::set_mode(sw_val);
}

void Micon::check_line() {}

#endif /* MICON_H */

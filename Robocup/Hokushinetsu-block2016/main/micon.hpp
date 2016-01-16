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
    static Motor* motor1;
    static Motor* motor2;
    static Motor* motor3;
    static BusIn* lines;
    static I2C* i2c_top;
    static I2C* i2c_bottom;
    static Compass* compass;
    static DigitalIn* ball;
    static DigitalOut* kick;
    static Ticker* flipper_sw;

    static void behaves(char);
    static void init();

private:
    Micon();
    static void check_sw();
    static void check_start_stop_sw(char);
    static void chmod(char);
};

void Micon::init() {
    motor1 = new Motor(p15, p16, p17);
    motor2 = new Motor(p17, p18, p22);
    motor3 = new Motor(p19, p20, p21);
    lines = new BusIn(p24, p25, p26, p29);
    i2c_top = new I2C(p9, p10);
    i2c_bottom = new I2C(p28, p27);
    compass = new Compass(p9, p10);
    ball = new DigitalIn(p11);
    kick = new DigitalOut(p12);

    flipper_sw->attach(&Micon::check_sw, 0.5);
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

#endif /* MICON_H */

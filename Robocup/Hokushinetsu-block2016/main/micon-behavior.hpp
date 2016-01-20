#ifndef MICON_BEHAVIOR_H
#define MICON_BEHAVIOR_H

class Micon;

class MiconBehavior {
public:
    static void run_normal();
    static void run_keeper();
    static void run_line_trace();
    static void run_kamikaze();
    static void run_debug_compass();
    static void run_debug_line();
    static void run_debug_kicker();
    static void run_debug_dribbler();
    static void run_debug_i2c();

private:
    MiconBehavior();
};

#include "micon.hpp"

void MiconBehavior::run_normal() {}
void MiconBehavior::run_keeper() {}

void MiconBehavior::run_line_trace() {}

void MiconBehavior::run_kamikaze() {
    char ir_data;
    Micon::i2c_bottom->read(IR_ADDRESS | 1, &ir_data, 1);
    if (ir_data <= 252) {
    }
}

void MiconBehavior::run_debug_compass() {
    float compass_value = Micon::compass->measure_angle();
    printf("%f\r\n",compass_value);

}
void MiconBehavior::run_debug_line() {
    int p = 1;

    float sound_pitch [7] = {
        261.626, 293.665, 329.628,
        349.228, 391.995, 440.000, 493.883
    };

    for (int i = 0; i < 4; i++) {
        if (Micon::lines[i]->read() == 1) {
            p++;
        }
    }

    Micon::sound->write(sound_pitch[p]);
}
void MiconBehavior::run_debug_kicker() {
    char sw_values[3];
    Micon::i2c_top->read(CONTROLER_ADDRESS | 1, sw_values, 3);

    if (sw_values[1] == 1) {
        Micon::kicker->kick();
    }

}

void MiconBehavior::run_debug_dribbler() {}

void MiconBehavior::run_debug_i2c() {ß
    Micon::flipper_line->detach();
    Micon::flipper_sw->detach();
    char sw_val[3];
    char ir_val;
    char ultrasonic_val[4];

    Micon::i2c_top->read(CONTROLER_ADDRESS | 1,  sw_val, 3);
    printf("switch\r\n  start-stop: %d\r\n    another: %d\r\n     rotaly: %d\r\n", sw_val[0], sw_val[1], sw_val[2]);

    Micon::i2c_bottom->read(IR_ADDRESS | 1, &ir_val, 1);
    printf("ir:\r\n  %d\r\n, %d\r\n", ir_val, (int)(ir_val / 252.0 * 360));

    printf("ultrasonic\r\n");
    Micon::i2c_top->read(ULTRASONIC_ADDRESS | 1, ultrasonic_val, 4);
    for(int i = 0; i < 4 ; i++) {
        printf(" %d :  %d\r\n", i + 1, ultrasonic_val[i]);
    }

    Micon::init();

}


#endif /* MICON_BEHAVIOR_H */

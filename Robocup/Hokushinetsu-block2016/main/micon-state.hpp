#ifndef MICON_STATE_H
#define MICON_STATE_H

#include "mbed.h"

class MiconState {
public:
    static bool is_running();
    static void set_run_state(bool);
    static char get_mode();
    static void set_mode(char);

private:
    MiconState();
    static bool run_state;
    static char mode;
};

bool MiconState::run_state = false;
char MiconState::mode = 0;

bool MiconState::is_running() {
    return run_state;
}

void MiconState::set_run_state(bool run_state_) {
    run_state = run_state_;
}

char MiconState::get_mode() {
    return mode;
}

void MiconState::set_mode(char mode_) {
    mode = mode_;
}

#endif /* MICON_STATE_H */

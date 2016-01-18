#ifndef SWITCH_CONTROL_H
#define SWITCH_CONTROL_H

class SwitchControl {
public:
    SwitchControl(PinName switch__);
    bool check_pressed();
    bool check_pressed_and_release();

private:
    DigitalIn switch_;
};

SwitchControl::SwitchControl(PinName switch__) : switch_(switch__) {}

bool check_pressed() {
    return switch_;
}

bool check_pressed_and_release() {
    if (switch_) {
        while (switch_)
            ;
        return true;
    }
    return false;
}

#endif /* SWITCH_CONTROL_H */

// [WIP]

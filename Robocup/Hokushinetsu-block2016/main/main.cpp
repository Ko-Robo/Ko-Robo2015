/**
 * @file   : main.cpp
 * @brief  : oversee all
 * @author : Shinnosuke KOIKE
 * @date   : 2016/01/16
 */

#include "mbed.h"
#include "micon.hpp"

int main(void) {
    Micon::init();
    while (1) {
        while (!MiconState::is_running())
            ;
        Micon::behaves(MiconState::get_mode());
    }
}

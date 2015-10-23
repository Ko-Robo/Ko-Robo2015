/**
 * @file   : limit.h (1.0)
 * @brief  : limit current and voltage
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/23
 */

#ifndef LIMIT_H
#define LIMIT_H

#include "mbed.h"

class Limit {
public:
    Limit(PinName current_, PinName voltage_);
    bool check_normal(void);

private:
    AnalogIn current;
    AnalogIn voltage;
};

Limit::Limit(PinName current_, PinName voltage_) :
        current(current_), voltage(voltage_) {
}

bool Limit::check_normal(void) {
    if (current > 10) return false;
    if (voltage > 30) return false;

    return true;
}

#endif /* LIMIT_H */

/**
 * example program

#include "mbed.h"
#include "limit.h"

int main(void) {
    bool normal
    Limit limit(PA_0, PA_1);
    while (1) {
        normal = limit.check_normal();
        if (normal == false) {
            // code
        }
    }
}
*/

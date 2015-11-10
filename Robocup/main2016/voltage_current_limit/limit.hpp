/**
 * @file   : limit.h (1.0)
 * @brief  : limit current and voltage
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/23
 */

#ifndef LIMIT_H
#define LIMIT_H

#include "mbed.h"
#include "INA226.hpp"

class Limit {
public:
    Limit(I2C i2c);
    void set_limit(double max_voltage, double max_current);
    bool check_normal(double *voltage, double *current);

private:
    INA226 voltage_current_monitor;
    double max_voltage;
    double max_current;
};

Limit::Limit(I2C i2c) : voltage_current_monitor(i2c) {
    unsigned short val;
    if (!voltage_current_monitor.isExist()) {
        while (1)
            ;
    } else if (voltage_current_monitor.rawRead(0x00, &val) != 0) {
        // debug.printf("voltage_current_monitor READ ERROR\r\n");
        while (1)
            ;
    }

    voltage_current_monitor.setCurrentCalibration();
}

void Limit::set_limit(double max_voltage, double max_current) {
    this->max_voltage = max_voltage;
    this->max_current = max_current;
}

bool Limit::check_normal(double *voltage, double *current) {
    voltage_current_monitor.getVoltage(voltage);
    voltage_current_monitor.getCurrent(current);

    if (*voltage > max_voltage) return false;
    if (*current > max_current) return false;

    return true;
}

#endif /* LIMIT_H */

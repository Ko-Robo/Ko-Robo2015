/**
 * @file   : communication.h (1.0)
 * @brief  : manage communication
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/23
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "mbed.h"

class CommuMaster {
public:
    CommuMaster(I2C i2cmaster_, int frequency);
    void receive_data(char addr, char data[]);
    void send_data(char addr, char data[]);

private:
    I2C* i2cmaster;
};

CommuMaster::CommuMaster(I2C i2cmaster_, int frequency) {
    i2cmaster = new I2C(i2cmaster_);
    i2cmaster->frequency(frequency);
}

void CommuMaster::receive_data(char addr, char data[]) {
    i2cmaster->read(addr | 1, data, 8, false);
}

void CommuMaster::send_data(char addr, char data[]) {
    i2cmaster->write(addr | 0, data, 8, false);
}

/**********************************************************/
class CommuSlave {
public:
    CommuSlave(I2CSlave i2cslave_, int frequency);
    void receive_data(char addr, char data[]);
    void send_data(char addr, char data[]);

private:
    I2CSlave* i2cslave;
};

CommuSlave::CommuSlave(I2CSlave i2cslave_, int frequency) {
    i2cslave = new I2CSlave(i2cslave_);
    i2cslave->frequency(frequency);
}

void CommuSlave::receive_data(char addr, char data[]) {
    i2cslave->address(addr);
    i2cslave->read(data, 8);
}

void CommuSlave::send_data(char addr, char data[]) {
    i2cslave->address(addr);
    i2cslave->write(data, 8);
}

#endif /* COMMUNICATION_H */

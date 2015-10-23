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

#endif

/**
 * example program(master)

#include "mbed.h"
#include "communication.h"

#define DATA_NUM    8

I2C i2cmaster(D5, D6);

int main(void) {
    int  freq = 2000;
    CommuMaster master(i2cmaster, freq);
    char addr = 0xA0;
    char data[DATA_NUM];

    while (1) {
        master.receive_data(addr, data);
        for (int i = 0; i < DATA_NUM; i++) {
            pc.printf("%d ", data[i]);      // display "1 1 0 0 0 0 0 1 "
        }
        pc.putchar('\n');
    }
}

 * example program(slave)

#include "mbed.h"
#include "communication.h"

I2CSlave i2cslave(D5, D6);

int main(void) {
    int  freq = 2000;
    CommuSlave slave(i2cslave, freq);
    char addr = 0xA0;
    char data[8] = {1, 1, 0, 0, 0, 0, 0, 1};

    while (1) {
        slave.send_data(addr, data);
    }
}
*/

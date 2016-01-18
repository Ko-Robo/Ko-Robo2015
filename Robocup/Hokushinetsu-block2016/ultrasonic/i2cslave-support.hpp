#ifndef I2C_SLAVE_SUPPORT_H
#define I2C_SLAVE_SUPPORT_H

class I2CSlaveSupport {
public:
    I2CSlaveSupport(PinName sda, PinName scl);
    bool do_i2c(char address, char *data, int data_length, char behavior);
    enum I2C_STATUS {
        NO_DATA      = I2CSlave::NoData,
        WRITE        = I2CSlave::ReadAddressed,
        READ_GENERAL = I2CSlave::WriteGeneral,
        READ         = I2CSlave::WriteAddressed
    };

private:
    I2CSlave* i2c_slave;
};

I2CSlaveSupport::I2CSlaveSupport(PinName sda, PinName scl) {
    i2c_slave = new I2CSlave(sda, scl);
}

bool I2CSlaveSupport::do_i2c(char address, char *data, int data_length, char behavior) {
    i2c_slave->address(address);
    int reception_check = i2c_slave->receive();

    if (reception_check != behavior) return false;

    switch (reception_check) {
        case WRITE:
            i2c_slave->write(data, data_length);
            i2c_slave->stop();
            break;
        case READ_GENERAL:
            // fall through
        case READ:
            i2c_slave->read(data, data_length);
            i2c_slave->stop();
            break;
        case NO_DATA:
            // fall through
        default:
            break;
    }
    return true;
}

#endif /* I2C_SLAVE_SUPPORT_H */

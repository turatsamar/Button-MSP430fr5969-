#include "PCF8574.h"


void PCF8574_init(void)
{
    I2C_init();
    __delay_cycles(1000);
}


unsigned char PCF8574_read(void)
{
    unsigned char port_byte = 0;

    I2C_start();
    I2C_write(PCF8574_read_cmd);
    port_byte = I2C_read(I2C_NACK);
    I2C_stop();

    return port_byte;
}


void PCF8574_write(unsigned char data_byte)
{
    I2C_start();
    I2C_write(PCF8574_write_cmd);
    I2C_ACK_NACK(I2C_ACK);
    I2C_write(data_byte);
    I2C_ACK_NACK(I2C_ACK);
    I2C_stop();
}

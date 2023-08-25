#include <I2C.h>


void I2C_init(void)
{
    SDA_DIR_OUT();
    SCL_DIR_OUT();
    __delay_cycles(1000);
    SDA_HIGH();
    SCL_HIGH();
}


void I2C_start(void)
{
    SDA_DIR_OUT();
    SDA_HIGH();
    SCL_HIGH();
    __delay_cycles(400);
    SDA_LOW();
    __delay_cycles(400);
    SCL_LOW();
}


void I2C_stop(void)
{
    SDA_DIR_OUT();
    SDA_LOW();
    SCL_LOW();
    __delay_cycles(400);
    SDA_HIGH();
    SCL_HIGH();
    __delay_cycles(400);
}


unsigned char I2C_read(unsigned char ack)
{
    unsigned char i = 8;
    unsigned char j = 0;

    SDA_DIR_IN();

    while(i > 0)
    {
        SCL_LOW();
        __delay_cycles(200);
        SCL_HIGH();
        __delay_cycles(200);
        j <<= 1;

        if(SDA_IN() != 0x00)
        {
            j++;
        }

        __delay_cycles(100);
        i--;
    };

    switch(ack)
    {
        case I2C_ACK:
        {
            I2C_ACK_NACK(I2C_ACK);
            break;
        }
        default:
        {
            I2C_ACK_NACK(I2C_NACK);
            break;
        }
    }

    return j;
}


void I2C_write(unsigned char value)
{
    unsigned char i = 8;

    SDA_DIR_OUT();
    SCL_LOW();

    while(i > 0)
    {

        if(((value & 0x80) >> 7) != 0x00)
        {
            SDA_HIGH();
        }
        else
        {
            SDA_LOW();
        }


        value <<= 1;
        __delay_cycles(200);
        SCL_HIGH();
        __delay_cycles(200);
        SCL_LOW();
        __delay_cycles(200);
        i--;
    };
}


void I2C_ACK_NACK(unsigned char mode)
{
    SCL_LOW();
    SDA_DIR_OUT();

    switch(mode)
    {
        case I2C_ACK:
        {
            SDA_LOW();
            break;
        }
        default:
        {
            SDA_HIGH();
            break;
        }
    }

    __delay_cycles(200);
    SCL_HIGH();
    __delay_cycles(200);
    SCL_LOW();
}


unsigned char I2C_wait_ACK(void)
{
    signed int timeout = 0;

    SDA_DIR_IN();

    SDA_HIGH();
    __delay_cycles(100);
    SCL_HIGH();
    __delay_cycles(100);

    while(SDA_IN() != 0x00)
    {
        timeout++;

        if(timeout > I2C_timeout)
        {
            I2C_stop();
            return 1;
        }
    };

    SCL_LOW();
    return 0;
}

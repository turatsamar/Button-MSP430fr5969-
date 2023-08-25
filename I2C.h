/*
 * I2C.h
 *
 *  Created on: 17 Aug 2023
 *      Author: turabek
 */

#ifndef I2C_H_
#define I2C_H_


#include "driverlib.h"



#define SW_I2C_SDA_PORT GPIO_PORT_P1
#define SW_I2C_SCL_PORT GPIO_PORT_P1

#define SDA_pin         GPIO_PIN6
#define SCL_pin         GPIO_PIN7

#define SDA_DIR_OUT()   GPIO_setAsOutputPin(SW_I2C_SDA_PORT, SDA_pin)
#define SDA_DIR_IN()    GPIO_setAsInputPin(SW_I2C_SDA_PORT, SDA_pin)
#define SCL_DIR_OUT()   GPIO_setAsOutputPin(SW_I2C_SCL_PORT, SCL_pin)
#define SCL_DIR_IN()    GPIO_setAsInputPin(SW_I2C_SCL_PORT, SCL_pin)

#define SDA_HIGH()      GPIO_setOutputHighOnPin(SW_I2C_SDA_PORT, SDA_pin)
#define SDA_LOW()       GPIO_setOutputLowOnPin(SW_I2C_SDA_PORT, SDA_pin)
#define SCL_HIGH()      GPIO_setOutputHighOnPin(SW_I2C_SCL_PORT, SCL_pin)
#define SCL_LOW()       GPIO_setOutputLowOnPin(SW_I2C_SCL_PORT, SCL_pin)

#define SDA_IN()        GPIO_getInputPinValue(SW_I2C_SDA_PORT, SDA_pin)

#define I2C_ACK         0xFF
#define I2C_NACK        0x00

#define I2C_timeout     1000


void I2C_init(void);
void I2C_start(void);
void I2C_stop(void);
unsigned char I2C_read(unsigned char ack);
void I2C_write(unsigned char value);
void I2C_ACK_NACK(unsigned char mode);
unsigned char I2C_wait_ACK(void);


#endif /* I2C_H_ */

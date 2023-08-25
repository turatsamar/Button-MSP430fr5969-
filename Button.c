/*
 * Button.c
 *
 *  Created on: 25 Aug 2023
 *      Author: turabek
 */


#include "driverlib.h"
#include "msp430fr5969.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "Button.h"
#include "lcd.h"
uint8_t sum;
char st[20];
uint8_t num;
char st1[20];
void SetButton (void)
{

    //Enable P1.1 internal resistance as pull-Up resistance
    GPIO_setAsInputPinWithPullUpResistor(
        GPIO_PORT_P4,
        GPIO_PIN5
        );
    GPIO_setAsInputPinWithPullUpResistor(
            GPIO_PORT_P1,
            GPIO_PIN1
            );

    //P1.1 Hi/Lo edge
    GPIO_selectInterruptEdge(
        GPIO_PORT_P4,
        GPIO_PIN5,
        GPIO_HIGH_TO_LOW_TRANSITION
        );
    GPIO_selectInterruptEdge(
            GPIO_PORT_P1,
            GPIO_PIN1,
            GPIO_HIGH_TO_LOW_TRANSITION
            );

    //P1.1 IFG cleared
    GPIO_clearInterrupt(
        GPIO_PORT_P4,
        GPIO_PIN5
        );
    GPIO_clearInterrupt(
           GPIO_PORT_P1,
           GPIO_PIN1
           );

    //P1.1 interrupt enabled
    GPIO_enableInterrupt(
        GPIO_PORT_P4,
        GPIO_PIN5
        );
    GPIO_enableInterrupt(
           GPIO_PORT_P1,
           GPIO_PIN1
           );

    LCD_goto(0,0);
    LCD_putstr("Input temp ");

     __bis_SR_register(GIE);


}


//This is the PORT1_VECTOR interrupt vector service routine




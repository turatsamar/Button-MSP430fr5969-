
#include "driverlib.h"
#include "msp430fr5969.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "lcd.h"
#include "Button.h"


void clockSet(void)
{
   GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_PJ,
        GPIO_PIN4 + GPIO_PIN5,
        GPIO_PRIMARY_MODULE_FUNCTION
    );


    //Set DCO frequency to 1 MHz
        CS_setDCOFreq(CS_DCORSEL_0,CS_DCOFSEL_0);
        //Set external clock frequency to 32.768 KHz
        CS_setExternalClockSource(32768,0);
        //Set ACLK=LFXT
        CS_initClockSignal(CS_ACLK,CS_LFXTCLK_SELECT,CS_CLOCK_DIVIDER_1);
        //Set SMCLK = DCO with frequency divider of 1
        CS_initClockSignal(CS_SMCLK,CS_DCOCLK_SELECT,CS_CLOCK_DIVIDER_1);
        //Set MCLK = DCO with frequency divider of 1
        CS_initClockSignal(CS_MCLK,CS_DCOCLK_SELECT,CS_CLOCK_DIVIDER_1);
        //Start XT1 with no time out
        CS_turnOnLFXT(CS_LFXT_DRIVE_0);
}

void Init_i2c(uint8_t Slave_Address)
{

    GPIO_setAsPeripheralModuleFunctionInputPin(
    	GPIO_PORT_P1,
    	GPIO_PIN6 + GPIO_PIN7,
    	GPIO_SECONDARY_MODULE_FUNCTION
    );

    EUSCI_B_I2C_initMasterParam param = {0};
    param.selectClockSource = EUSCI_B_I2C_CLOCKSOURCE_SMCLK;
    param.i2cClk = CS_getSMCLK();
    param.dataRate = EUSCI_B_I2C_SET_DATA_RATE_400KBPS;
    param.byteCounterThreshold = 0;
    param.autoSTOPGeneration = EUSCI_B_I2C_SEND_STOP_AUTOMATICALLY_ON_BYTECOUNT_THRESHOLD;
    EUSCI_B_I2C_initMaster(EUSCI_B0_BASE, &param);

    //Specify slave address
    UCB0I2CSA =  Slave_Address;

    //Enable I2C Module to start operations
    UCB0CTLW0 &= ~(UCSWRST);
    PM5CTL0 &= ~LOCKLPM5;

}
bool uartInit(void)
{

    GPIO_setAsPeripheralModuleFunctionInputPin(
    GPIO_PORT_P2,
    GPIO_PIN0 + GPIO_PIN1,
    GPIO_SECONDARY_MODULE_FUNCTION
    );

    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_ACLK;
    param.clockPrescalar = 3;
    param.firstModReg = 0;
    param.secondModReg = 0x92;
    param.parity = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode = EUSCI_A_UART_MODE;
    param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if (STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A0_BASE, &param)) {
        return false;
    }

    EUSCI_A_UART_enable(EUSCI_A0_BASE);

    return true;
}

void UART_SendByte(uint16_t byte)
{
    while (!(UCA0IFG & UCTXIFG)); // ÑGÑtÑuÑ} ÑsÑÄÑÑÑÄÑrÑ~ÑÄÑÉÑÑÑy ÑtÑ|Ñë ÑÅÑuÑÇÑuÑtÑpÑâÑy
    UCA0TXBUF = byte;
}
void UART_SendString(char* str)
{
    int i = 0;
    while (str[i] != '\0') {
        UART_SendByte(str[i]); // Send each character of the string
        i++;
    }
}




char st[20];
uint8_t sum;
char st1[20];
void main (void)
{



    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);




    clockSet();
    uartInit();
    Init_i2c(0x27);
    PMM_unlockLPM5();
    LCD_init();
    LCD_clear_home();
    SetButton ();
    sprintf(st,"%d", sum);
    LCD_putstr(st1);
    LCD_goto(0,3);
    LCD_putstr("d");


}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT4_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(PORT4_VECTOR)))
#endif
void Port_4 (void)
{

    	sum= sum + 1;

    	if(sum==25){
    		sum=0;
    		LCD_send(clear_display, CMD);
    	}

        LCD_goto(11,0);
        sprintf(st,"%d", sum);
        LCD_putstr(st);

    //P1.1 IFG cleared
    GPIO_clearInterrupt(
        GPIO_PORT_P4,
        GPIO_PIN5
        );
}
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(PORT1_VECTOR)))
#endif
void  Port_1 (void)
{

        LCD_goto(0,1);
        LCD_putstr("Success");
        LCD_goto(9,1);
        LCD_putstr(st);


    //P1.1 IFG cleared
    GPIO_clearInterrupt(
        GPIO_PORT_P1,
        GPIO_PIN1
        );

}








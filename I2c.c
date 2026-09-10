#include<xc.h>
#include "I2c.h"

void I2C_init()
{
    SCL_PORT = ENABLE ;
    SDA_PORT = ENABLE ;

    SLEW_RATE  = STD_SPEED_MODE ;
    
    MASTER_MODE_BIT_3  = CLOCK_BIT_3 ; 
    MASTER_MODE_BIT_2  = CLOCK_BIT_2 ;
    MASTER_MODE_BIT_1  = CLOCK_BIT_1 ;
    MASTER_MODE_BIT_0  = CLOCK_BIT_0 ;

    SSPCON2 = 0x00 ;

    BAUD_RATE_SETTING = CLOCK_SPEED ;

    SYN_SERIAL_ENABLE_BIT = ENABLE_PORT_SCL_SDA ;

}

void I2c_Start()
{
    START_BIT = INITIATE_ON_SDA_SCL;
    while(START_BIT);
    MSSP_INTERRUPT_FLAG = 0;
}

void I2c_Write(unsigned char data)
{
    SERIAL_Tx_Rx_BUFFER = data;

    while(MSSP_INTERRUPT_FLAG != 1);
    
    MSSP_INTERRUPT_FLAG = 0;

}

void I2c_Stop()
{
    STOP_BIT = INITIATE_STOP;
    while(STOP_BIT);
    MSSP_INTERRUPT_FLAG = 0;
}

unsigned char I2c_Read()
{
    unsigned char data ;

    RECIEVE_ENABLE_BIT = ENABLE_RECIVE;
    while(!MSSP_INTERRUPT_FLAG);

    MSSP_INTERRUPT_FLAG = 0;

    data = SERIAL_Tx_Rx_BUFFER ;

    return data;
}

void I2c_ACK()
{
    ACKNOWLEDGE_DATA_BIT = ACKNOWLEDGE ;
    ACKNOWLEDGE_SEQU_ENABLE = INITIATE_ACK_SEQU;

    while(ACKNOWLEDGE_SEQU_ENABLE);
    MSSP_INTERRUPT_FLAG = 0;
}

void I2c_NACK(void)
{
    ACKNOWLEDGE_DATA_BIT = NOT_ACKNOWLEDGE ;
    ACKNOWLEDGE_SEQU_ENABLE = INITIATE_ACK_SEQU;

    while(ACKNOWLEDGE_SEQU_ENABLE);
    MSSP_INTERRUPT_FLAG = 0;
}




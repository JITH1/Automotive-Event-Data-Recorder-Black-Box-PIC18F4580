#include<xc.h>
#include "UART.h"

void init_uart(void)
{
    
	RX_PIN = 1;
	TX_PIN = 0;

	BAUD_RATE_16_BIT = ENABLE_16_BIT_BAUD ;
    BAUD_RATE_SELECT_BIT = HIGH_SPEED ;
    BAUD_RATE_HIGH = HIGH_VALUE ;
    BAUD_RATE_LOW = LOW_VALUE ;
    
    EUSART_MODE = ASYNCHRONOUS ;
    BIT_TRANSMISSION = EIGHT_BIT;
    TRANSMIT_ENABLE = ENABLE_TRANSMIT;
    SEND_BREAK_CHAR_BIT = BREAK_TXN_COMPLETED;
    
    RECIVE_BIT_ENABLE = EIGHT_BIT_RECIEVE;
    CONTINUOUS_RECIVE = ENABLE_CONT_RECIEVE;
    SERIAL_PORT = SERIAL_PORT_ENABLED ;
    
    AUTO_BAUD_DETECT = DISABLE ;
	/* TX interrupt flag bit */
	Tx_INT_FLAG = 0;

	/* RX interrupt enable bit */
	Rx_INT_FLAG = 0;
    
}

void put_ch(unsigned char byte) 
{
	/* Output one byte */
	/* Set when register is empty */
	while(!Tx_INT_FLAG)
	{
		continue;
	}
	Tx_INT_FLAG = 0;
	TXREG = byte;
} 

int puts(const char *s)
{
	while(*s)		
	{
		put_ch(*s++);	
	}
	return 0;
}

unsigned char get_ch(void)
{
	/* Retrieve one byte */
	/* Set when register is not empty */
	while(!RCIF)
	{
		continue;
	}
	RCIF = 0;
	return RCREG;
}

unsigned char getche(void)
{
	unsigned char c;

	put_ch(c = get_ch());

	return (c);
}







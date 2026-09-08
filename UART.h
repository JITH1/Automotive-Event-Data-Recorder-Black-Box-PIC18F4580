#ifndef UART_H
#define UART_H

#define RX_PIN					      TRISC7
#define TX_PIN					      TRISC6

#define BAUD_RATE_16_BIT              BAUDCONbits.BRG16
#define ENABLE_16_BIT_BAUD            1

#define BAUD_RATE_SELECT_BIT          TXSTAbits.BRGH
#define HIGH_SPEED                    1

#define BAUD_RATE_HIGH                SPBRGH
#define BAUD_RATE_LOW                 SPBRG
#define HIGH_VALUE                    0x02
#define LOW_VALUE                     0x08
#define AUTO_BAUD_DETECT              BAUDCONbits.ABDEN

#define EUSART_MODE                   TXSTAbits.SYNC
#define ASYNCHRONOUS                  0
#define BIT_TRANSMISSION              TXSTAbits.TX9
#define EIGHT_BIT                     0
#define TRANSMIT_ENABLE               TXSTAbits.TXEN
#define ENABLE_TRANSMIT               1
#define SEND_BREAK_CHAR_BIT           TXSTAbits.SENDB
#define BREAK_TXN_COMPLETED           0

#define RECIVE_BIT_ENABLE             RCSTAbits.RX9
#define EIGHT_BIT_RECIEVE             0
#define CONTINUOUS_RECIVE             RCSTAbits.CREN
#define ENABLE_CONT_RECIEVE           1
#define DISABLE                       0
#define SERIAL_PORT                   RCSTAbits.SPEN
#define SERIAL_PORT_ENABLED            1

#define Tx_INT_FLAG                   PIR1bits.TXIF
#define Rx_INT_FLAG                   PIR1bits.RCIF

void init_uart(void);
void put_ch(unsigned char byte);
int puts(const char *s);
unsigned char get_ch(void);
unsigned char getche(void);

#endif
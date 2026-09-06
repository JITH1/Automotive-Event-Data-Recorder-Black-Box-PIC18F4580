#ifndef I2C_H
#define I2C_H

#define SLEW_RATE                     SSPSTATbits.SMP
#define STD_SPEED_MODE                1  

#define MASTER_MODE_BIT_3             SSPCON1bits.SSPM3
#define MASTER_MODE_BIT_2             SSPCON1bits.SSPM2  
#define MASTER_MODE_BIT_1             SSPCON1bits.SSPM1 
#define MASTER_MODE_BIT_0             SSPCON1bits.SSPM0 

#define CLOCK_BIT_3                   1
#define CLOCK_BIT_2                   0
#define CLOCK_BIT_1                   0
#define CLOCK_BIT_0                   0

#define BAUD_RATE_SETTING             SSPADD
#define CLOCK_SPEED                   49

#define  START_BIT                    SSPCON2bits.SEN 
#define  INITIATE_ON_SDA_SCL          1 

#define SERIAL_Tx_Rx_BUFFER           SSPBUF

#define MSSP_INTERRUPT_FLAG           PIR1bits.SSPIF

#define STOP_BIT                      SSPCON2bits.PEN
#define INITIATE_STOP                 1

#define RECIEVE_ENABLE_BIT            SSPCON2bits.RCEN
#define ENABLE_RECIVE                 1  

#define ACKNOWLEDGE_DATA_BIT          SSPCON2bits.ACKDT 
#define ACKNOWLEDGE                   0
#define NOT_ACKNOWLEDGE               1

#define ACKNOWLEDGE_SEQU_ENABLE       SSPCON2bits.ACKEN
#define INITIATE_ACK_SEQU             1

#define SYN_SERIAL_ENABLE_BIT         SSPCON1bits.SSPEN
#define ENABLE_PORT_SCL_SDA           1   

#define SCL_PORT                      TRISCbits.TRISC3
#define SDA_PORT                      TRISCbits.TRISC4 

#define ENABLE                        1

void I2C_init(void);
void I2c_Start(void);
void I2c_Write(unsigned char data);
void I2c_Stop(void);
void I2c_ACK(void);
void I2c_NACK(void);
unsigned char I2c_Read(void);

#endif




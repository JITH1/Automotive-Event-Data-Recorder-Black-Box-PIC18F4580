#ifndef Ds1307_H
#define Ds1307_H

#define SLAVE_READ		0xD1
#define SLAVE_WRITE		0xD0


#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07

void init_ds1307(void);

void write_ds1307(unsigned char address,  unsigned char data);
unsigned char read_ds1307(unsigned char address);
void get_time(void);
void set_RTC(void);
void set_log(unsigned char sec ,unsigned char min ,unsigned char hr);

extern unsigned char time[9];
extern unsigned char clock_reg[3];

extern unsigned int log_hold;
extern unsigned int field_hold;

#endif 
#include<xc.h>
#include "ds1307.h"
#include "I2c.h"
#include "Ext_EEPROM.h"
#include "Matrix_keypad.h"
#include "clcd.h"
#include "Clock.h"
#include <stdio.h>

unsigned char time[9];
unsigned char clock_reg[3];

unsigned int log_hold = 0;
unsigned int field_hold = 0;

void init_ds1307()
{
    unsigned char dummy;

	/* Setting the CH bit of the RTC to Stop the Clock */
	dummy = read_ds1307(SEC_ADDR);
	write_ds1307(SEC_ADDR, dummy | 0x80); 

	/* Seting 12 Hr Format */
	dummy = read_ds1307(HOUR_ADDR);
	write_ds1307(HOUR_ADDR, dummy | 0x40); 

	/* 
	 * Control Register of DS1307
	 * Bit 7 - OUT
	 * Bit 6 - 0
	 * Bit 5 - OSF
	 * Bit 4 - SQWE
	 * Bit 3 - 0
	 * Bit 2 - 0
	 * Bit 1 - RS1
	 * Bit 0 - RS0
	 * 
	 * Seting RS0 and RS1 as 11 to achive SQW out at 32.768 KHz
	 */ 
	write_ds1307(CNTL_ADDR, 0x93); 

	/* Clearing the CH bit of the RTC to Start the Clock */
	dummy = read_ds1307(SEC_ADDR);
	write_ds1307(SEC_ADDR, dummy & 0x7F); 
}

void write_ds1307(unsigned char address,  unsigned char data)
{
    I2c_Start();
    I2c_Write(SLAVE_WRITE);
    I2c_Write(address);
    I2c_Write(data);
    I2c_Stop();
}

unsigned char read_ds1307(unsigned char address)
{
    unsigned char data;

	I2c_Start();
	I2c_Write(SLAVE_WRITE);
	I2c_Write(address);
	repeated_Start();
	I2c_Write(SLAVE_READ);
	data = I2c_Read();
	I2c_Stop();

	return data;
}

void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}

void set_RTC()
{
    unsigned char sec = 0x00;
    unsigned char min = 0x00;
    unsigned char hr = 0x00;
    unsigned char field = 0x00;
    
    unsigned char rtc[17] ;
    unsigned char op = 0x00;
    unsigned char *fields[] = {"FLD:SEC","FLD:MIN","FLD:Hr"}; 
    
    log_hold = 0x04E2;
    field_hold = 5;
    scroll = 10;
            
    while(log_hold)
    {
        
        if(scroll == 0)
        {
            if(((op = _read_switch()) == MK_SW11) && (field < 3))
            {
                field++;
            }
            else if((op == MK_SW12) && (field > 0 ))
            {
                field--;
            }
            else if(op == MK_SW12 && (field == 0 ))
            {
                break;
            }  
                
            scroll = 10; 
        } 
        
        if(field_hold == 0)
        {
            if((op == MK_SW11) && (field == 3 ))
            {
               set_log(sec,min,hr);
               break;
            }  
            else if((op == MK_SW1) && (field == 0))
            {
               sec++;
               sec = sec % 60;
            }
            else if((op == MK_SW2) && (field == 0))
            {
               if(sec > 0)
               sec--;    
            }
            else if((op == MK_SW1) && (field == 1))
            {
               min++;
               min = min % 60;
            }
            else if((op == MK_SW2) && (field == 1))
            {
               if(min > 0)
               min--;    
            }
            else if((op == MK_SW1) && (field == 2))
            {
                hr++;
                hr = hr % 12;
            }
            else if((op == MK_SW2) && (field == 2))
            {
               if(hr > 0)
               hr--;    
            }
            
            field_hold = 5;
            
        } 
        
        sprintf(rtc,"%s %02d:%02d:%02d",fields[field],hr,min,sec);
        clcd_print("SET RTC :       ",LINE1(0));
        clcd_print(rtc,LINE2(0));
          
    }    
    
}

void set_log(unsigned char sec ,unsigned char min ,unsigned char hr)
{
    unsigned char rtc_buffer[3] = {0x00,0x00,0x00};
    
    rtc_buffer[0] = ((sec/10)<<4)| ((sec%10) & 0x0F);
    
    rtc_buffer[1] = ((min/10)<<4) | ((min%10) & 0x0F);
            
    rtc_buffer[2] = 0x40 | ((hr / 10) << 4) | ((hr % 10) & 0x0F);
    
    I2c_Start();
    I2c_Write(SLAVE_WRITE);
    I2c_Write(SEC_ADDR);

    for(int i = 0; i<3 ; i++)
    {
        I2c_Write(rtc_buffer[i]);
    }
     
    I2c_Stop();
    
    hold = 100;
            
    while(hold)
    {
        clcd_print("<--- RTC SET -->",LINE1(0));
        clcd_print("   UPDATED RTC  ",LINE2(0));
    }    
    
}


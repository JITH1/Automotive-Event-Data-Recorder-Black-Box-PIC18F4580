#include<xc.h>
#include "Ext_EEPROM.h"
#include "I2c.h"
#include "clcd.h"

volatile unsigned char write_count = 0;
volatile unsigned char address = 0x00;

unsigned char store_string[16][17];

void EEPROM_wrtie(unsigned char *Tx_string)
{

     I2c_Start();

     I2c_Write(0xA0);
     
     I2c_Write(address);

     for(int i = 0; i<16 ; i++)
     {
         I2c_Write(Tx_string[i]);
     }

     I2c_Stop();

     if(write_count < 16)
     {
        write_count++; 
     }

     address = (address+16) % 256 ; // Circular buffer

}

void EEPROM_read(unsigned char str[][17])
{
     unsigned char read = 0;
     unsigned char i;

     if(write_count == 0)
     {
          clcd_print("EEPROM EMPTY",LINE2(4));
          return;
     }

     I2c_Start();

     I2c_Write(0xA0);
     I2c_Write(0x00);

     I2c_Start();
     I2c_Write(0xA1);

     while(read < write_count)
     {

         for(i = 0 ; i<16 ; i++)
         {
             str[read][i] = I2c_Read();  

             if(read == (write_count - 1) && (i == 15))
             {
                 I2c_NACK();
             }
             else
             {
                I2c_ACK();
             }

         }
        
         str[read][i] = '\0';

         read++;
         
     }

     I2c_Stop();

}

void EEPROM_clear()
{
    if(write_count == 0)
    {
        clcd_print("EEPROM EMPTY",LINE2(4));
        return;
    }
    
    unsigned char clear = 0;

    while(clear < write_count)
    {

        I2c_Start();

        I2c_Write(0xA0);

        I2c_Write(clear * 16);

        for(int i = 0 ; i < 16 ; i++)
        {
            I2c_Write(0x00);
        }

        I2c_Stop();

        clear++;
    }

    write_count = 0;
    address = 0x00;

}


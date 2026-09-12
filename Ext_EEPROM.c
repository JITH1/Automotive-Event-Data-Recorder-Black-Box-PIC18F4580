#include<xc.h>
#include "Ext_EEPROM.h"
#include "I2c.h"
#include "clcd.h"
#include "Clock.h"

volatile unsigned char write_count = 0;
volatile unsigned char address = 0x08;    // Write Starting address

unsigned char store_string[16][17];

void EEPROM_wrtie(unsigned char *Tx_string)
{
     I2c_Start();
     I2c_Write(0xA0);
     I2c_Write(0x00);
     I2c_Write(0xAA);
     I2c_Stop();
     EEPROM_wait_ready();
    
     I2c_Start();
     I2c_Write(0xA0);
     I2c_Write(address);

     for(int i = 0; i<8 ; i++)
     {
         I2c_Write(Tx_string[i]);
     }
     
     I2c_Stop();
     EEPROM_wait_ready();
     
     I2c_Start();
     I2c_Write(0xA0);
     I2c_Write(address+8);
     
     for(int i = 8; i<16 ; i++)
     {
         I2c_Write(Tx_string[i]);
     }

     I2c_Stop();
     EEPROM_wait_ready();

     if(write_count < 15)
     {
        write_count++; 
     }
     
     I2c_Start();
     I2c_Write(0xA0);
     I2c_Write(0x01);
     I2c_Write(write_count);
     I2c_Stop();
     EEPROM_wait_ready();
     
     address = (address+16) % 256 ; // Circular buffer

}

void EEPROM_read(unsigned char str[][17])
{
     unsigned char read = 0;
     unsigned char i;

     unsigned char flag = 0x00 ;
   
     I2c_Start();
     I2c_Write(0xA0);
     I2c_Write(0x00);
     repeated_Start();
     I2c_Write(0xA1);
     
     flag = I2c_Read();
     
     if(flag == 0xAA)
     {
         I2c_ACK();                 // ACK the flag byte so the EEPROM sends the next one
         write_count = I2c_Read();
 
         if(write_count == 0x00)
         {
             I2c_NACK();            // nothing more to read, terminate the transfer
             I2c_Stop();
 
             scroll = 100;
             while(scroll)
             {
                 clcd_print("EEPROM IS EMPTY",LINE1(0));
                 clcd_print("                ",LINE2(0));
             }
             return;
         }  
         
         I2c_NACK();                // last header byte we need; terminate this transfer
         I2c_Stop();

         I2c_Start();
         I2c_Write(0xA0);
         I2c_Write(0x08);
         repeated_Start();
         I2c_Write(0xA1);
         
     }
     else 
     {
         I2c_NACK();                // not a valid log, terminate the transfer
         I2c_Stop();
 
         scroll = 100;
         while(scroll)
         {
            clcd_print("EEPROM IS EMPTY",LINE1(0));
            clcd_print("                ",LINE2(0));
         }
         return;

     }    

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
    
     unsigned char flag = 0x00 ;
     
     I2c_Start();
     I2c_Write(0xA0);
     I2c_Write(0x00);
     repeated_Start();
     I2c_Write(0xA1);
     flag = I2c_Read();
     
     if(flag == 0xAA)
     {
         I2c_ACK();                 // ACK the flag byte so the EEPROM sends the next one
         write_count = I2c_Read();
 
         if(write_count == 0x00)
         {
             I2c_NACK();            // nothing more to read, terminate the transfer
             I2c_Stop();
 
             scroll = 100;
             while(scroll)
             {
                 clcd_print("EEPROM IS EMPTY",LINE1(0));
                 clcd_print("                ",LINE2(0));
             }
             return;
         }    
         
         I2c_NACK();                // last header byte we need; terminate this transfer
    
     }
     else 
     {
         I2c_NACK();                // not a valid log, terminate the transfer
         I2c_Stop();
 
         scroll = 100;
         while(scroll)
         {
            clcd_print("EEPROM IS EMPTY",LINE1(0));
            clcd_print("                ",LINE2(0));
         }
         return;
     }    
    
    I2c_Stop();
     
    unsigned char clear = 0;

    while(clear < write_count)
    {

        I2c_Start();

        I2c_Write(0xA0);
        I2c_Write((clear * 16) + 8 );

        for(int i = 0 ; i < 8 ; i++)
        {
            I2c_Write(0x00);
        }

        I2c_Stop();
        EEPROM_wait_ready();

        I2c_Start();

        I2c_Write(0xA0);

        I2c_Write((clear*16)+16);

        for(int i = 0 ; i < 8 ; i++)
        {
            I2c_Write(0x00);
        }

        I2c_Stop();
        EEPROM_wait_ready();
        
        clear++;
        
    }

     I2c_Start();
     I2c_Write(0xA0);
     I2c_Write(0x01);
     I2c_Write(0x00);
     I2c_Stop();
     EEPROM_wait_ready();
     
    write_count = 0;
    address = 0x08;
    
    scroll = 100;
        
    while(scroll)
    {
        clcd_print("EEPROM CLEARED  ",LINE1(0));
        clcd_print("                ",LINE2(0));
    } 
    
    return ;
}

void EEPROM_wait_ready()
{
    do
    {
        I2c_Start();

        SERIAL_Tx_Rx_BUFFER = 0xA0;

        while(MSSP_INTERRUPT_FLAG != 1);

        MSSP_INTERRUPT_FLAG = 0;

    } while(SSPCON2bits.ACKSTAT);   // ACKSTAT=1 means NACK, still busy

    I2c_Stop();

}

void repeated_Start()
{  
   SSPCON2bits.RSEN = 1;
   while(SSPCON2bits.RSEN); 
   MSSP_INTERRUPT_FLAG = 0;
}    

#include<xc.h>
#include "Matrix_keypad.h"

unsigned char key ;
unsigned char gear ;
unsigned char gear_buff[6] = {'N','1','2','3','4','5'};

void _init_matrix_key(void)
{
    PORTB_CONFIG = DIGITAL ;                    // Config PORTB as digital 
    PORTB_DIRECTION = DIRECTION_CONFIG ;        // config Row as output(RB7 - RB5,RB3 & RB2) and Column as input(RB1 and RB4)
    PORTB_PULL_UP = 0;                          //  Make port B input as pull up for coloumns 

    MATRIX_PORT = MATRIX_PORT | 0xEC ;

}

unsigned char _read_switch()
{
    ROW1 = LOW;
    ROW2 = HIGH;
    ROW3 = HIGH;

    if(COL1 == 0)
    {
        return MK_SW1;
    }

    ROW1 = HIGH;
    ROW2 = LOW;
    ROW3 = HIGH;

    if(COL1 == 0)
    {
        return MK_SW2;
    }
    else if(COL4 == 0)
    {
        return MK_SW11;
    }

    ROW1 = HIGH;
    ROW2 = HIGH;
    ROW3 = LOW;
    ROW3 = LOW;

    if(COL1 == 0)
    {
        return MK_SW3;
    }
    else if(COL4 == 0)
    {
        return MK_SW12;
    }

    return ALL_RELEASED ;

}

unsigned char _read_key()
{
     static unsigned char flag = 1 ;
     unsigned char key = _read_switch();

     if(( key != ALL_RELEASED) && (flag == 1))
     {
          flag = 0;
          return key;     
     }
     else if(key == ALL_RELEASED)
     {
        flag = 1;
     }
     
     return ALL_RELEASED ;
}

void _switch_function()
{

     key = _read_key();
         
     if(key == 1)
     {
         if(gear < 5)
         {
            gear++;
         }
    
     }
     else if(key == 2)
     {
        if(gear > 0)
        {
            gear--;
        }
    }

}


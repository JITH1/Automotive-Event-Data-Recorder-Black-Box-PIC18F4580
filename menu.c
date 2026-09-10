#include <xc.h>
#include "Menu.h"
#include "Matrix_keypad.h"
#include "Clock.h"
#include "clcd.h"
#include "Ext_EEPROM.h"
#include "UART.h"

volatile unsigned int menu_timer = 0;

void display_menu()
{
        menu_timer = 0x04E2;
        scroll = 10;
        unsigned char *line_1[] = {"->1.View Log      ","  1.View Log    ","->3.Set Log     ","  3.Set Log     "};
        unsigned char *line_2[] = {"  2.Download Log","->2.Download Log","  4.Clear Log   ","->4.Clear Log   "};
        unsigned char down = 0x00;
        unsigned char op = 0x00;
        
        do
        { 
            clcd_print(line_1[down],LINE1(0));
            clcd_print(line_2[down],LINE2(0));
            
            if(scroll == 0)
            {
                if(((op = _read_switch()) == MK_SW1) && (down < 3))
                {
                    down++;
                }
                else if((op == MK_SW2) && (down > 0 ))
                {
                    down--;
                }
                else if(op == MK_SW12)
                {
                    break;
                }  
                
                scroll = 10; 
            }   
            
                if((op == MK_SW11) && (down == 0))
                {
                    view_log(); 
                }
                else if((op == MK_SW11) && (down == 1))
                {
                    download_log();
                }
                else if((op == MK_SW11) && (down == 2))
                {
                    // Set Log
                }
                else if((op == MK_SW11) && (down == 3))
                {
                    EEPROM_clear();
                }    
                
            
        }while(menu_timer);  
        
}

void view_log()
{
    EEPROM_read(store_string);
    menu_timer = 0x04E2;
    scroll = 100;
    
    if(!write_count)
    {
        while(scroll)
        {
            clcd_print("EEPROM IS EMPTY",LINE1(0));
            clcd_print("                ",LINE2(0));
        }    
        return ;
    }
    else 
    {
        scroll = 10;
    }    
    
    unsigned char down = 0x00;
    unsigned char op = 0x00;
    
    while(menu_timer && (write_count > 0))
    {
     
        clcd_print(store_string[down%write_count],LINE1(0));
        
        if((down+1) == write_count)
        {
            clcd_print("                ",LINE2(0));
        }
        else
        {
            clcd_print(store_string[(down+1)%write_count],LINE2(0));
        }    
        
        if(scroll == 0)
        {
            if(((op = _read_switch()) == MK_SW1) && (down < write_count - 1))
            {
                down++;
            }
            else if((op == MK_SW2) && (down > 0 ))
            {
                down--;
            }
            else if(op == MK_SW12)
            {
                break;
            }    
            
            scroll = 10;
            
        }    
    }    
       
}

void download_log()
{
    if(!write_count)
    {
        puts("EEPROM IS EMPTY...!");
        puts("\r\n");
        return;
    }    
        
    EEPROM_read(store_string);
    
    puts("\r\n/----BLACK BOX LOG----/\r\n\r\n");
    puts("   RTC   GEAR SPEED\r\n\r\n");
        
    for(int i = 0; i<write_count ; i++)
    {
        puts(store_string[i]);
        puts("\r\n\r\n");
    }
    
    puts("/----------------------------/");
    
}

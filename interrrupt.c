#include<xc.h>
#include "Enable.h"


void _enable_interrupt()
{
    INTCONbits.GIE = GLOBAL_INTERRUPT_SET;
    INTCONbits.PEIE = PERIPHERAL_INTERRUPT_SET;
}

void __interrupt() isr(void)
{
    if(ADC_INTERRUPT_FLAG == 1)
    {
        speed = ((unsigned int)ADC_RESULT_HIGH_REG<<8) | (unsigned int)ADC_RESULT_LOW_REG ;
        ADC_INTERRUPT_FLAG = 0;
    }
    
    if(PIR1bits.TMR1IF == 1)
    {
       
        TMR1 = TIMER1_PRELOAD ;
        
        if(hold > 0)
        {
            hold-- ;
        }
        
        if(scroll > 0)
        {
            scroll--;
        }
        
        if(menu_timer > 0)
        {
            menu_timer--;
        }
        
        if(log_hold > 0)
        {
            log_hold--;
        }
        
        if(field_hold > 0)
        {
            field_hold--;
        }    

        PIR1bits.TMR1IF = 0;
    }
    
}


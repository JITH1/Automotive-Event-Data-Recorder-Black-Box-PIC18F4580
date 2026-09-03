#include<xc.h>
#include "Enable.h"

void _enable_interrupt()
{
    INTCONbits.GIE = GLOBAL_INTERRUPT_SET;
    INTCONbits.PIE = PERIPHERAL_INTERRUPT_SET;
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
        count++;
        TMR1 = TIMER1_PRELOAD ;

        if(count == 50)
        {
            count =0;
            sec++;
            
            if(sec == 60)
            {
                sec = 0;
                min = ++min ;

                if(min%60 == 0)
                {
                    min = 0;
                    hr = (++hr)%24;
                }
            }
        }

        PIR1bits.TMR1IF = 0;
    }
    
}


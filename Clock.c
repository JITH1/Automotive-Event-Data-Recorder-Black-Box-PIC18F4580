#include<xc.h>
#include"Clock.h"

volatile unsigned char sec = 0;
volatile unsigned char min = 0;
volatile unsigned char hr = 0;

volatile unsigned char count = 0;

void _init_timer1(void)
{
    INTCONbits.GIE = GLOBAL_INTERRUPT_SET;
    INTCONbits.PIE = PERIPHERAL_INTERRUPT_SET;
    PIE1bits.TMR1IE = TIMER1_INTERRUPT_SET;
    PIR1bits.TMR1IF = TIMER1_INTERRUPT_FLAG;
    
    T1CONbits.TICKPS1 = TIMER1_PRESCALE_BIT_1;
    T1CONbits.TICKPS0 = TIMER1_PRESCALE_BIT_0;
    T1CONbits.T1OSCEN = TIMER1_OSCILLATOR_SELECT;
    T1CONbits.TMR1CS = TIMER1_CLOCK_SOURCE;
    T1CONbits.TMR1ON = TIMER1_ENABLE;

    TMR1 = TIMER1_PRELOAD ;

}

void __interrupt() isr(void)
{
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


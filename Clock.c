#include<xc.h>
#include"Clock.h"

volatile unsigned char sec = 0;
volatile unsigned char min = 0;
volatile unsigned char hr = 0;

volatile unsigned char count = 0;

void _init_timer1(void)
{

    PIE1bits.TMR1IE = TIMER1_INTERRUPT_SET;
    PIR1bits.TMR1IF = TIMER1_INTERRUPT_FLAG;
    
    T1CONbits.T1CKPS1 = TIMER1_PRESCALE_BIT_1;
    T1CONbits.T1CKPS0 = TIMER1_PRESCALE_BIT_0;
    T1CONbits.T1OSCEN = TIMER1_OSCILLATOR_SELECT;
    T1CONbits.TMR1CS = TIMER1_CLOCK_SOURCE;
    T1CONbits.TMR1ON = TIMER1_ENABLE;

    TMR1 = TIMER1_PRELOAD ;

}

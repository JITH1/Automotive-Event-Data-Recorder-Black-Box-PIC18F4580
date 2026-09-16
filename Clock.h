#ifndef CLOCK_H
#define CLOCK_H

#define TIMER1_INTERRUPT_SET           1
#define TIMER1_INTERRUPT_FLAG          0
#define TIMER1_PRESCALE_BIT_1          0
#define TIMER1_PRESCALE_BIT_0          1
#define TIMER1_OSCILLATOR_SELECT       0
#define TIMER1_CLOCK_SOURCE            0
#define TIMER1_ENABLE                  1
#define TIMER1_PRELOAD                 15536

extern volatile unsigned char hold ;

extern volatile unsigned char scroll;

void _init_timer1(void);

#endif
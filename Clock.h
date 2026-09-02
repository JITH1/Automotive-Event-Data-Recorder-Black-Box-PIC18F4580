#ifndef CLOCK_H
#define CLOCK_H

#define GLOBAL_INTERRUPT_SET           1
#define PERIPHERAL_INTERRUPT_SET      1
#define TIMER1_INTERRUPT_SET           1
#define TIMER1_INTERRUPT_FLAG          0
#define TIMER1_PRESCALE_BIT_1          0
#define TIMER1_PRESCALE_BIT_0          1
#define TIMER1_OSCILLATOR_SELECT       0
#define TIMER1_CLOCK_SOURCE            0
#define TIMER1_ENABLE                  1
#define TIMER1_PRELOAD                 15536

extern volatile unsigned char sec;
extern volatile unsigned char min;
extern volatile unsigned char hr;

extern volatile unsigned char count;

void _init_timer1(void);

#endif
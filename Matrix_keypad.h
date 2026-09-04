#ifndef KEY_H
#define KEY_H

#define PORTB_CONFIG                             ADCON1
#define DIGITAL                                 0x0F
#define PORTB_DIRECTION                         TRISB
#define DIRECTION_CONFIG                        0x12
#define PORTB_PULL_UP                           RBPU 
#define MATRIX_PORT                             PORTB

#define ROW3                                    PORTBbits.RB7
#define ROW2                                    PORTBbits.RB6
#define ROW1                                    PORTBbits.RB5

#define COL4                                    PORTBbits.RB4
#define COL1                                    PORTBbits.RB1

#define MK_SW1                                  1
#define MK_SW2                                  2
#define MK_SW3                                  3

#define MK_SW11                                 11
#define MK_SW12                                 12

#define ALL_RELEASED                            0xFF

#define HIGH                                    1
#define LOW                                     0

extern unsigned char key;
extern unsigned char gear_buff[6];
extern unsigned char gear ;

void _init_matrix_key(void);
unsigned char _read_switch(void);
unsigned char _read_key(void);
void _switch_function(void);

#endif
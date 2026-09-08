#include<xc.h>
#include "Clock.h"
#include "clcd.h"
#include "adc.h"
#include "Enable.h"
#include "Matrix_keypad.h"
#include "I2c.h"
#include "UART.h"


void main()
{
    _enable_interrupt();
    _init_timer1();
    init_clcd();
    _init_matrix_key();
    _init_adc();
    I2C_init();
    init_uart();

    while(1)
    {
        _switch_function();
        _get_speed();
        get_line2(line2_buffer);
        clcd_print(line1_buffer,LINE1(0));
        clcd_print(line2_buffer,LINE2(0));
    }

}
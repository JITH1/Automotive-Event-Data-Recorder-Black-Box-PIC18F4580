#include<xc.h>
#include "Clock.h"
#include "clcd.h"
#include "adc.h"
#include "Enable.h"


void main()
{
    _enable_interrupt();
    _init_timer1();
    init_clcd();
    _init_adc();

    while(1)
    {
        _get_speed();
        get_line2(line2_buffer);
        clcd_print(line1_buffer,LINE1(0));
        clcd_print(line2_buffer,LINE2(0));
    }

}
#include<xc.h>
#include"Clock.h"
#include"clcd.h"

void main()
{
    _init_timer1();
    init_clcd();

    while()
    {
        get_line2(line2_buffer);
        clcd_print(line1_buffer,LINE1(0));
        clcd_print(line2_buffer,LINE2(0));
    }

}
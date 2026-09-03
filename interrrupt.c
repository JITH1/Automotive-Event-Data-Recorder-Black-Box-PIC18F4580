#include<xc.h>
#include "Enable.h"

void _enable_interrupt()
{
    INTCONbits.GIE = GLOBAL_INTERRUPT_SET;
    INTCONbits.PIE = PERIPHERAL_INTERRUPT_SET;
}
#ifndef INT_EN 
#define INT_EN

#include "adc.h"
#include "clock.h"

#define GLOBAL_INTERRUPT_SET           1
#define PERIPHERAL_INTERRUPT_SET       1

void _enable_interrupt(void);

#endif
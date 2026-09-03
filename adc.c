#include<xc.h>
#include "adc.h"

unsigned int speed = 0;

void _init_adc(void)
{
    CHANNEL_SELECT_BIT_3 = CHANNEL5_BIT_3;
    CHANNEL_SELECT_BIT_2 = CHANNEL5_BIT_2;
    CHANNEL_SELECT_BIT_1 = CHANNEL5_BIT_1;
    CHANNEL_SELECT_BIT_0 = CHANNEL5_BIT_0;

    V_REF_CONFIG_BIT_1  = SET_AVss;
    V_REF_CONFIG_BIT_0 =  SET_AVdd;

    RESULT_JUSTIFICATION = RIGHT_JUSTIFIED;

    AQCUISITION_BIT_2 = TAD_8_BIT_2; 
    AQCUISITION_BIT_1 = TAD_8_BIT_1;
    AQCUISITION_BIT_0 = TAD_8_BIT_0;

    CONV_CLK_BIT_2  = Fosc_32_BIT_2;
    CONV_CLK_BIT_1  = Fosc_32_BIT_1;
    CONV_CLK_BIT_0 =  Fosc_32_BIT_0;

    ADC_RESULT_HIGH_REG = 0x00;
    ADC_RESULT_LOW_REG = 0x00;
    
    ADC_INTERRUPT_ENaBLE = 1;
    ADC_INTERRUPT_FLAG = 0;

    ENABLE_ADC = 1;

}

void _get_speed()
{
    CONVERSION_STATUS_BIT = 1;
}

void __interrupt() isr(void)
{
    if(ADC_INTERRUPT_FLAG == 1)
    {
        speed = ((unsigned int)ADC_RESULT_HIGH_REG<<8) | (unsigned int)ADC_RESULT_LOW_REG ;
        ADC_INTERRUPT_FLAG = 0;
    }

}
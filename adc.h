#ifndef ADC_H
#define ADC_H

#define CHANNEL4_BIT_3         0
#define CHANNEL4_BIT_2         1
#define CHANNEL4_BIT_1         0
#define CHANNEL4_BIT_0         0

#define CHANNEL_SELECT_BIT_3   ADCON0bits.CHS3 
#define CHANNEL_SELECT_BIT_2   ADCON0bits.CHS2
#define CHANNEL_SELECT_BIT_1   ADCON0bits.CHS1
#define CHANNEL_SELECT_BIT_0   ADCON0bits.CHS0

#define V_REF_CONFIG_BIT_1     ADCON1bits.VCFG1
#define V_REF_CONFIG_BIT_0     ADCON1bits.VCFG0 

#define SET_AVss               0
#define SET_AVdd               0

#define RESULT_JUSTIFICATION   ADCON2bits.ADFM 
#define RIGHT_JUSTIFIED        1

#define AQCUISITION_BIT_2      ADCON2bits.ACQT2 
#define AQCUISITION_BIT_1      ADCON2bits.ACQT1 
#define AQCUISITION_BIT_0      ADCON2bits.ACQT0

#define TAD_8_BIT_2            1
#define TAD_8_BIT_1            0
#define TAD_8_BIT_0            0

#define CONV_CLK_BIT_2         ADCON2bits.ADCS2
#define CONV_CLK_BIT_1         ADCON2bits.ADCS1
#define CONV_CLK_BIT_0         ADCON2bits.ADCS0

#define Fosc_32_BIT_2          0
#define Fosc_32_BIT_1          1
#define Fosc_32_BIT_0          0

#define ADC_RESULT_HIGH_REG    ADRESH
#define ADC_RESULT_LOW_REG     ADRESL

#define ADC_INTERRUPT_ENaBLE   PIE1bits.ADIE
#define ADC_INTERRUPT_FLAG     PIR1bits.ADIF

#define ENABLE_ADC             ADCON0bits.ADON 
#define CONVERSION_STATUS_BIT  ADCON0bits.GO

extern unsigned int speed;

void _get_speed(void);
void _init_adc(void);

#endif
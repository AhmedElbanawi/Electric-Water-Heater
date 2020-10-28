/******************************************************************************/
#ifndef ADC_H
#include "ADC.h"
#endif
/******************************************************************************/
void ADC_Inite(const ADC_CLK_SRC_t ADC_CLK_SRC){
               /* Disable ADC and Select ADC Clock Source */
     ADCON0 = (ADC_CLK_SRC << 6);
     ADCON1 = (ADC_CLK_SRC >> 2) << 6;
               /*------------------------------------------*/
     CLEAR_BIT(PIE1, 6);            /* Disable ADC Interrupt */
     CLEAR_BIT(PIR1, 6);            /* Clear ADC Flag */
     SET_BIT(ADCON1, 7);            /* Right justified */
}
void ADC_Select_Analog_Channels(const ADC_SELECT_ANALOG_CHANNELS_t ADC_SELECT){
     ADCON1 &= 0XF0;                  /* Inite Selection of Analog and Digital Channels */
     if(ADC_SELECT > 6){
        ADCON1 |= (1 + ADC_SELECT);   /* Select Required Analog and Digital Channels */
     }
     else{
        ADCON1 |= ADC_SELECT;         /* Select Required Analog and Digital Channels */
     }
     TRISE |= 0X07;                   /* Define AN5, AN6, AN7 as Input */
     TRISA |= 0X2F;                   /* Define AN0, AN1, AN2, AN3, AN4 as Input */
}
void ADC_Start(const ADC_CHANNEL_t ADC_CHANNEL){
     delay_us(30);     /* time delay between two reading as min = 2 TAD */
                       /* Select required Channel */
     ADCON0 &= 0XC0;
     ADCON0 |= (ADC_CHANNEL << 3);
                    /*--------------------------*/
                     /* clear adc buffer */
     ADRESH = 0X00;
     ADRESL = 0X00;
                     /*--------------------------*/
     SET_BIT(ADCON0, 0);  /* Enable ADC */
     delay_us(30);        /* Sampling Time */
     SET_BIT(ADCON0, 2);  /* ADC Active */
}
u16_t ADC_Read_Buffer(void){
         return ( ( ( (u16_t)ADRESH ) << 8 ) | ADRESL);   /* Read ADC Buffers */
}
void ADC_Stop(void){
     CLEAR_BIT(ADCON0, 0);  /* Disable ADC */
}
void ADC_Enable_Interrupt(void){
     SET_BIT(PIE1, 6);      /* Enable ADC Interrupt */
}
void ADC_Disable_Interrupt(void){
     CLEAR_BIT(PIE1, 6);       /* Disable ADC Interrupt */
}
void ADC_Clear_Flag(void){
     CLEAR_BIT(PIR1, 6);       /* Clear ADC Flag */
}
u8_t ADC_Read_Flag(void){
     return GET_BIT(PIR1, 6);  /* Read ADC Flag */
}
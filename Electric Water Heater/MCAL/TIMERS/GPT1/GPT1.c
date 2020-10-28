/******************************************************************************/
#ifndef GPT1_H
#include "GPT1.h"
#endif
/******************************************************************************/
void GPT1_Prescaler_Update(const GPT1_Prescaler_t GPT1_PRESCALER){
     switch(GPT1_PRESCALER){
            case GPT1_PRESCALER_1_TO_1:
                 CLEAR_BIT(T1CON, 4);
                 CLEAR_BIT(T1CON, 5);
                 break;
            case GPT1_PRESCALER_1_TO_2:
                 SET_BIT(T1CON, 4);
                 CLEAR_BIT(T1CON, 5);
                 break;
            case GPT1_PRESCALER_1_TO_4:
                 CLEAR_BIT(T1CON, 4);
                 SET_BIT(T1CON, 5);
                 break;
            case GPT1_PRESCALER_1_TO_8:
                 SET_BIT(T1CON, 4);
                 SET_BIT(T1CON, 5);
                 break;
            default:
                 /* Error: Undefined Prescaler */
                 break;
     }
}
void GPT1_Buffer_Low_Update(const u8_t GPT1_BUFFER_LOW_UPDATE_VAL){
     TMR1L = GPT1_BUFFER_LOW_UPDATE_VAL;
}
void GPT1_Buffer_High_Update(const u8_t GPT1_BUFFER_HIGH_UPDATE_VAL){
     TMR1H = GPT1_BUFFER_HIGH_UPDATE_VAL;
}
void GPT1_Start(void){
     SET_BIT(T1CON, 0);
}
void GPT1_Stop(void){
     CLEAR_BIT(T1CON, 0);
}
void GPT1_OSC_Enable(void){
     SET_BIT(T1CON, 3);
}
void GPT1_OSC_Disable(void){
     CLEAR_BIT(T1CON, 3);
}
void GPT1_Interrupt_Enable(void){
     SET_BIT(PIE1, 0);
}
void GPT1_Interrupt_Disable(void){
     CLEAR_BIT(PIE1, 0);
}
void GPT1_Flag_Clear(void){
     CLEAR_BIT(PIR1, 0);
}
GPT1_Flag_t GPT1_Flag_Read(void){
     GPT1_Flag_t GPT1_Flag;
     if(GPT1_OVERFLOW_OCCURED == GET_BIT(PIR1, 0)){
        GPT1_Flag = GPT1_OVERFLOW_OCCURED;
     }else{
        GPT1_Flag = GPT1_OVERFLOW_NOT_OCCURED;
     }
     return GPT1_Flag;
}
void GPT1_Synchronization_Enable(void){
     CLEAR_BIT(T1CON, 2);
}
void GPT1_Synchronization_Disable(void){
     SET_BIT(T1CON, 2);
}
void GPT1_Init(const GPT1_CLK_SRC_t GPT1_CLK_SRC){
     T1CON = 0X00; /* GPT1 Stop, OSC Disable, Synchronization Enable, Prescaler 1 To 1*/
     TMR1H = 0X00; /* Clear Timer1 High Buffer*/
     TMR1L = 0X00; /* Clear Timer1 Low Buffer*/
     if(GPT1_CLK_SRC_EXTERNAL == GPT1_CLK_SRC){
        SET_BIT(T1CON, 1);
     }else{
        CLEAR_BIT(T1CON, 1); /* GPT1_CLK_SRC_INTERNAL*/
     }
     CLEAR_BIT(PIR1, 0); /* Clear Timer1 Flag */
     CLEAR_BIT(PIE1, 0); /* Disable Timer1 Interrupt */
}
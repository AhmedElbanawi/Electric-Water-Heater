/******************************************************************************/
#ifndef GPT0_H
#include "GPT0.h"
#endif
/******************************************************************************/
void GPT0_Init(const GPT0_CLK_SRC_t GPT0_CLK_SRC){
     OPTION_REG = 0XFF;
     TMR0 = 0X00; /* Clear Timer0 Buffer */
     if(GPT0_CLK_SRC_EXTERNAL == GPT0_CLK_SRC){
        SET_BIT(OPTION_REG, 5);
     }else{
        CLEAR_BIT(OPTION_REG, 5);
     }
     CLEAR_BIT(INTCON, 2); /* Clear Timer0 Flag */
     CLEAR_BIT(INTCON, 5); /* Disable Timer0 Interrupt */
}
void GPT0_Interrupt_Disable(void){
     CLEAR_BIT(INTCON, 5);
}
void GPT0_Interrupt_Enable(void){
     SET_BIT(INTCON, 5);
}
void GPT0_Flag_Clear(void){
     CLEAR_BIT(INTCON, 2);
}
GPT0_Flag_t GPT0_Flag_Read(void){
     GPT0_Flag_t GPT0_Flag;
     if(GPT0_OVERFLOW_OCCURED == GET_BIT(INTCON, 2)){
        GPT0_Flag = GPT0_OVERFLOW_OCCURED;
     }else{
        GPT0_Flag = GPT0_OVERFLOW_NOT_OCCURED;
     }
     return GPT0_Flag;
}
void GPT0_Start(void){
     CLEAR_BIT(OPTION_REG, 3);
}
void GPT0_Stop(void){
     SET_BIT(OPTION_REG, 3);
}
void GPT0_Count_Rising_Edge(void){
     CLEAR_BIT(OPTION_REG, 4);
}
void GPT0_Count_Falling_Edge(void){
     SET_BIT(OPTION_REG, 4);
}
void GPT0_Prescaler_Update(const GPT0_Prescaler_t GPT0_PRESCALER){
     OPTION_REG &= 0XF8;
     switch(GPT0_PRESCALER){
            case GPT0_PRESCALER_1_TO_2:
                 OPTION_REG |= GPT0_PRESCALER;
                 break;
            case GPT0_PRESCALER_1_TO_4:
                 OPTION_REG |= GPT0_PRESCALER;
                 break;
            case GPT0_PRESCALER_1_TO_8:
                 OPTION_REG |= GPT0_PRESCALER;
                 break;
            case GPT0_PRESCALER_1_TO_16:
                 OPTION_REG |= GPT0_PRESCALER;
                 break;
            case GPT0_PRESCALER_1_TO_32:
                 OPTION_REG |= GPT0_PRESCALER;
                 break;
            case GPT0_PRESCALER_1_TO_64:
                 OPTION_REG |= GPT0_PRESCALER;
                 break;
           case GPT0_PRESCALER_1_TO_128:
                 OPTION_REG |= GPT0_PRESCALER;
                 break;
           case GPT0_PRESCALER_1_TO_256:
                 OPTION_REG |= GPT0_PRESCALER;
                 break;
           default:
                 /* Error: Undefined Prescaler */
                 break;
     }
}
void GPT0_Buffer_Update(const u8_t GPT0_BUFFER_UPDATE_VAL){
     TMR0 = GPT0_BUFFER_UPDATE_VAL;
}
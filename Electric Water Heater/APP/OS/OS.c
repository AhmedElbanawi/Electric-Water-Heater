/******************************************************************************/
#ifndef OS_H
#include "OS.h"
#endif
/******************************************************************************/
#ifndef INT_H
#include "INT.h"
#endif
/******************************************************************************/
#ifndef GPT2_H
#include "GPT2.h"
#endif
/******************************************************************************/
volatile Bool_t OS_Update = TRUE;
void OS_Tick_Init(void){
     INT_Global_Init();
     GPT2_Init();
                 /* Tick = 5 Ms */
     GPT2_Scaler_Update(GPT2_PRESCALER_1_TO_4, GPT2_POSTSCALER_1_TO_5);
     GPT2_Update_us(250);
     GPT2_Interrupt_Enable();
     INT_Global_Enable();
     GPT2_Start();
}
void Interrupt(void){
     if(GPT2_OVERFLOW_OCCURED == GPT2_Flag_Read()){
        GPT2_Flag_Clear();
        OS_Update = TRUE;
     }
}
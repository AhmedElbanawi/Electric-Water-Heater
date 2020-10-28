/******************************************************************************/
#ifndef GPT1_H
#define GPT1_H
#endif
/******************************************************************************/
#ifndef SYS_DATA_TYPES_H
#include "Sys_Data_Types.h"
#endif
/******************************************************************************/
#ifndef BIT_MANIPULATION_H
#include "Bit_Manipulation.h"
#endif
/******************************************************************************/
typedef enum{
        GPT1_CLK_SRC_INTERNAL = 0,
        GPT1_CLK_SRC_EXTERNAL
}GPT1_CLK_SRC_t;
typedef enum{
        GPT1_PRESCALER_1_TO_1 = 0,
        GPT1_PRESCALER_1_TO_2,
        GPT1_PRESCALER_1_TO_4,
        GPT1_PRESCALER_1_TO_8
}GPT1_Prescaler_t;
typedef enum{
        GPT1_OVERFLOW_NOT_OCCURED = 0,
        GPT1_OVERFLOW_OCCURED
}GPT1_Flag_t;
/******************************************************************************/
void GPT1_Interrupt_Enable(void);
void GPT1_Interrupt_Disable(void);
void GPT1_Flag_Clear(void);
GPT1_Flag_t GPT1_Flag_Read(void);
void GPT1_Start(void);
void GPT1_Stop(void);
void GPT1_Init(const GPT1_CLK_SRC_t GPT1_CLK_SRC);
void GPT1_OSC_Enable(void);
void GPT1_OSC_Disable(void);
void GPT1_Buffer_Low_Update(const u8_t GPT1_BUFFER_LOW_UPDATE_VAL);
void GPT1_Buffer_High_Update(const u8_t GPT1_BUFFER_HIGH_UPDATE_VAL);
void GPT1_Prescaler_Update(const GPT1_Prescaler_t GPT1_PRESCALER);
void GPT1_Synchronization_Enable(void);
void GPT1_Synchronization_Disable(void);
/******************************************************************************/
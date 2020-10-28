/******************************************************************************/
#ifndef GPT0_H
#define GPT0_H
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
        GPT0_CLK_SRC_INTERNAL = 0,
        GPT0_CLK_SRC_EXTERNAL
}GPT0_CLK_SRC_t;
typedef enum{
        GPT0_PRESCALER_1_TO_2 = 0,
        GPT0_PRESCALER_1_TO_4,
        GPT0_PRESCALER_1_TO_8,
        GPT0_PRESCALER_1_TO_16,
        GPT0_PRESCALER_1_TO_32,
        GPT0_PRESCALER_1_TO_64,
        GPT0_PRESCALER_1_TO_128,
        GPT0_PRESCALER_1_TO_256
}GPT0_Prescaler_t;
typedef enum{
        GPT0_OVERFLOW_NOT_OCCURED = 0,
        GPT0_OVERFLOW_OCCURED
}GPT0_Flag_t;
/******************************************************************************/
void GPT0_Interrupt_Enable(void);
void GPT0_Interrupt_Disable(void);
void GPT0_Flag_Clear(void);
GPT0_Flag_t GPT0_Flag_Read(void);
void GPT0_Start(void);
void GPT0_Stop(void);
void GPT0_Init(const GPT0_CLK_SRC_t GPT0_CLK_SRC);
void GPT0_Buffer_Update(const u8_t GPT0_BUFFER_UPDATE_VAL);
void GPT0_Prescaler_Update(const GPT0_Prescaler_t GPT0_PRESCALER);
void GPT0_Count_Rising_Edge(void);
void GPT0_Count_Falling_Edge(void);
/******************************************************************************/
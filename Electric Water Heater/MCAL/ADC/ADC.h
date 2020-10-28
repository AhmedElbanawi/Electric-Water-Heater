/******************************************************************************/
#ifndef ADC_H
#define ADC_H
#endif
/******************************************************************************/
#ifndef BIT_MANIPULATION_H
#include "Bit_Manipulation.h"
#endif
/******************************************************************************/
#ifndef SYS_DATA_TYPES_H
#include "Sys_Data_Types.h"
#endif
/******************************************************************************/
typedef enum{
                           /* AN7    AN6     AN5     AN4     AN3      AN2        AN1    AN0    VREF+   VREF-  */
        ADC_SELECT0 = 0,   /* A       A       A       A       A          A        A      A      VDD     VSS   */
        ADC_SELECT1,       /* A       A       A       A      VREF+       A        A      A      AN3     VSS   */
        ADC_SELECT2,       /* D       D       D       A       A          A        A      A      VDD     VSS   */
        ADC_SELECT3,       /* D       D       D       A       VREF+      A        A      A      AN3     VSS   */
        ADC_SELECT4,       /* D       D       D       D       A          D        A      A      VDD     VSS   */
        ADC_SELECT5,      /*  D       D       D       D       VREF+      D        A      A      AN3     VSS   */
        ADC_SELECT6,      /*  D       D       D       D       D          D        D      D      —       —     */
        ADC_SELECT7,       /* A       A       A       A        VREF+   VREF-      A      A       AN3    AN2   */
        ADC_SELECT8,       /* D       D       A       A        A         A        A      A       VDD    VSS   */
        ADC_SELECT9,       /* D       D       A       A        VREF+    A         A      A       AN3    VSS   */
        ADC_SELECT10,      /* D       D       A       A        VREF+    VREF-     A      A       AN3    AN2   */
        ADC_SELECT11,      /* D       D       D       A        VREF+    VREF-     A      A       AN3    AN2   */
        ADC_SELECT12,     /*  D       D       D       D        VREF+    VREF-     A      A       AN3    AN2   */
        ADC_SELECT13,     /*  D       D       D       D        D         D        D      A       VDD    VSS   */
        ADC_SELECT14       /* D       D       D       D        VREF+     VREF-    D      A       AN3    AN2   */
}ADC_SELECT_ANALOG_CHANNELS_t;
typedef enum{
        ADC_CH0 = 0,
        ADC_CH1,
        ADC_CH2,
        ADC_CH3,
        ADC_CH4,
        ADC_CH5,
        ADC_CH6,
        ADC_CH7
}ADC_CHANNEL_t;
typedef enum{
        ADC_CLK_SRC_2TOSC =  0,       /* FOSC <= 1.25 MHZ */
        ADC_CLK_SRC_4TOSC =  4,       /* FOSC <= 2.5  MHZ */
        ADC_CLK_SRC_8TOSC =  1,       /* FOSC <= 5    MHZ */
        ADC_CLK_SRC_16TOSC = 5,       /* FOSC <= 10   MHZ */
        ADC_CLK_SRC_32TOSC = 2,       /* FOSC <= 20   MHZ */
        ADC_CLK_SRC_64TOSC = 6        /* FOSC <= 20   MHZ */
}ADC_CLK_SRC_t;
void ADC_Inite(const ADC_CLK_SRC_t ADC_CLK_SRC);
void ADC_Select_Analog_Channels(const ADC_SELECT_ANALOG_CHANNELS_t ADC_SELECT);
void ADC_Start(const ADC_CHANNEL_t ADC_CHANNEL);
void ADC_Stop(void);
u16_t ADC_Read_Buffer(void);
void ADC_Enable_Interrupt(void);
void ADC_Disable_Interrupt(void);
void ADC_Clear_Flag(void);
u8_t ADC_Read_Flag(void);
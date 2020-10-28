/******************************************************************************/
#ifndef TMP_SENSOR_H
#include "TMP_SENSOR.h"
#endif
/******************************************************************************/
#ifndef ADC_H
#include "ADC.h"
#endif
/******************************************************************************/
#define ENDED 0
#define TMP_SENSOR_PERIOD_100_MS 5
/******************************************************************************/
typedef enum{
        SW_STATE_OFF = 0,
        SW_STATE_ON
}SW_STATE_t;
typedef enum{
        SW_POWER = 0,
        SW_UP,
        SW_DOWN,
        SW_MAX_NUMBER
}SW_t;
typedef enum{
        TMP_SENSOR_MODE_OFF = 0,
        TMP_SENSOR_MODE_ON
}TMP_SENSOR_MODE_t;
/******************************************************************************/
extern Bool_t SW_Period_Is_Ended(void);
extern SW_State_t SW_Read(const SW_t SW_ID);
extern void TMP_Avg_Update(const Bool_t AVG_UPDATE_ENABLE);
/******************************************************************************/
u8_t TMP_SENSOR_Read(void);
/******************************************************************************/
static u8_t TMP_SENSOR_Reading_Val = 0;
static Bool_t TMP_SENSOR_Period_Ended = FALSE;
/******************************************************************************/
void TMP_SENSOR_Init(void){
     ADC_Inite(ADC_CLK_SRC_8TOSC);
     ADC_Select_Analog_Channels(ADC_SELECT0);
}
/******************************************************************************/
void TMP_SENSOR_Update(void){
     static u8_t TMP_SENSOR_Period = TMP_SENSOR_PERIOD_100_MS;
     static TMP_SENSOR_MODE_t TMP_SENSOR_Mode = TMP_SENSOR_MODE_OFF; /* Hint */
     if(TRUE == SW_Period_Is_Ended()){
        switch(TMP_SENSOR_Mode){
               case TMP_SENSOR_MODE_OFF:
                    if(SW_STATE_ON == SW_Read(SW_POWER)){
                       TMP_SENSOR_Mode = TMP_SENSOR_MODE_ON;
                       TMP_SENSOR_Period = TMP_SENSOR_PERIOD_100_MS;
                    }
                    break;
               case TMP_SENSOR_MODE_ON:
                    if(SW_STATE_ON == SW_Read(SW_POWER)){
                       TMP_SENSOR_Mode = TMP_SENSOR_MODE_OFF;
                    }
                    else{
                       TMP_SENSOR_Period_Ended = FALSE;
                       TMP_SENSOR_Period--;
                       if(ENDED == TMP_SENSOR_Period){
                          ADC_Start(ADC_CH0);
                          TMP_SENSOR_Period_Ended = TRUE;
                          while(0 == ADC_Read_Flag());
                          TMP_SENSOR_Reading_Val = (ADC_Read_Buffer() * 5) / 10;
                          ADC_Clear_Flag();
                          TMP_SENSOR_Period = TMP_SENSOR_PERIOD_100_MS;
                          TMP_Avg_Update(TRUE);
                       }
                    }
                    break;
               default:
                    /* Error: Undefined TMP_SENSOR_MODE */
                    break;
        }
     }
}
/******************************************************************************/
u8_t TMP_SENSOR_Read(void){
     return TMP_SENSOR_Reading_Val;
}
/******************************************************************************/
/******************************************************************************/
#ifndef TMP_H
#include "TMP.h"
#endif
/******************************************************************************/
#ifndef SYS_DATA_TYPES_H
#include "Sys_Data_Types.h"
#endif
/******************************************************************************/
#define MAX_TMP 75
#define MIN_TMP 35
#define TMP_SETTING_PERIOD_5_SEC 250
#define ENDED 0
#define TMP_CONST 5
#define NO_OF_READINGS 10
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
        TMP_MODE_OFF = 0,
        TMP_MODE_ON_NORMAL,
        TMP_MODE_ON_SETTING
}TMP_MODE_t;
/******************************************************************************/
static void TMP_Required_Update(void);
static void TMP_Sensed_Update(void);
extern Bool_t SW_Period_Is_Ended(void);
extern SW_State_t SW_Read(const SW_t SW_ID);
extern void SSD_Set_Symbol(const u8_t SYMBOL);
extern u8_t TMP_SENSOR_Read(void);
extern void HEATER_Set(u8_t TMP_REQ, u8_t TMP_AVG, Bool_t UPDATE);
extern void COOLER_Set(const u8_t REQ_TMP, const u8_t AVG_TMP, const Bool_t UPDATE_ENABLE);
extern void TMP_Avg_Update(const Bool_t AVG_UPDATE_ENABLE);
extern void EEPROM_Store(const u8_t DATA, const Bool_t UPDATE_ENABLE);
/******************************************************************************/
u8_t TMP_Required = 60;
u16_t Avg_Tmp = 0;
static TMP_MODE_t TMP_Mode = TMP_MODE_OFF;
static Bool_t Update_Avg_Tmp = FALSE;
/******************************************************************************/
void TMP_Update(void){
     TMP_Required_Update(); /* Every 20 ms */
     TMP_Sensed_Update();   /* Every 1000 ms */
}
/******************************************************************************/
static void TMP_Required_Update(void){
       static u8_t TMP_Setting_Period = TMP_SETTING_PERIOD_5_SEC;
       if(TRUE == SW_Period_Is_Ended()){
          switch(TMP_Mode){
              case TMP_MODE_OFF:
                   if(SW_STATE_ON == SW_Read(SW_POWER)){
                      TMP_Mode = TMP_MODE_ON_NORMAL;
                   }
                   break;
              case TMP_MODE_ON_NORMAL:
                   if(SW_STATE_ON == SW_Read(SW_POWER)){
                      TMP_Mode = TMP_MODE_OFF;
                   }
                   else if(SW_STATE_ON == SW_Read(SW_UP) || SW_STATE_ON == SW_Read(SW_DOWN)){
                      TMP_Mode = TMP_MODE_ON_SETTING;
                      TMP_Setting_Period = TMP_SETTING_PERIOD_5_SEC;
                   }
                   break;
              case TMP_MODE_ON_SETTING:
                   if(SW_STATE_ON == SW_Read(SW_POWER)){
                      TMP_Mode = TMP_MODE_OFF;
                   }
                   else if(TMP_Setting_Period != ENDED){
                      if(SW_STATE_ON == SW_Read(SW_UP) && TMP_Required < MAX_TMP){
                         TMP_Required += TMP_CONST;
                         TMP_Setting_Period = TMP_SETTING_PERIOD_5_SEC;
                         EEPROM_Store(TMP_Required, TRUE);
                      }
                      else if(SW_STATE_ON == SW_Read(SW_DOWN) && TMP_Required > MIN_TMP){
                         TMP_Required -= TMP_CONST;
                         TMP_Setting_Period = TMP_SETTING_PERIOD_5_SEC;
                         EEPROM_Store(TMP_Required, TRUE);
                      }
                      TMP_Setting_Period--;
                      if(ENDED == TMP_Setting_Period){
                         TMP_Mode = TMP_MODE_ON_NORMAL;
                      }
                   }
                   break;
           }
           SSD_Set_Symbol(TMP_Required);
       }
}
/******************************************************************************/
static void TMP_Sensed_Update(void){
       static u8_t Counter = NO_OF_READINGS;
       if(TRUE == Update_Avg_Tmp){
          switch(TMP_Mode){
                  case TMP_MODE_OFF:
                       Counter = NO_OF_READINGS;
                       Avg_Tmp = 0;
                       break;
                  case TMP_MODE_ON_NORMAL:
                  case TMP_MODE_ON_SETTING:
                       Counter--;
                       Avg_Tmp += TMP_SENSOR_Read();
                       if(ENDED == Counter){
                          Counter = NO_OF_READINGS;
                          Avg_Tmp /= NO_OF_READINGS;
                          HEATER_Set(TMP_Required, Avg_Tmp, TRUE);
                          COOLER_Set(TMP_Required, Avg_Tmp, TRUE);
                          Avg_Tmp = 0;
                       }
                       break;
          }
          Update_Avg_Tmp = FALSE;
       }
}
/******************************************************************************/
void TMP_Avg_Update(const Bool_t AVG_UPDATE_ENABLE){
     Update_Avg_Tmp = AVG_UPDATE_ENABLE;
}
/******************************************************************************/
/******************************************************************************/
#ifndef HEATER_H
#include "HEATER.h"
#endif
/******************************************************************************/
typedef enum{
        HEATER_MODE_POWER_OFF = 0,
        HEATER_MODE_OFF,
        HEATER_MODE_ON
}HEATER_MODE_t;
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
        LED_MODE_OFF = 0,
        LED_MODE_ON,
        LED_MODE_BLINKING
}LED_MODE_t;
/******************************************************************************/
void HEATER_Set(const u8_t REQ_TMP, const u8_t AVG_TMP, const Bool_t UPDATE_ENABLE);
static void Heater_On(void);
static void Heater_Off(void);
static void HEATER_Update_Mode(void);
extern Bool_t SW_Period_Is_Ended(void);
SW_State_t SW_Read(const SW_t SW_ID);
void LED_Set_Mode(const LED_MODE_t MODE, const Bool_t LED_UPDATE_ENABLE);
/******************************************************************************/
static s8_t Tmp_Req = 0, Tmp_Avg = 0;
static Bool_t Update = FALSE;
static HEATER_MODE_t HEATER_Mode = HEATER_MODE_POWER_OFF;
/******************************************************************************/
void HEATER_Init(void){
     GPIO_SetPinDirection(HEATER_PORT_ID, HEATER_PIN_ID, HEATER_DIRECTION_ID);
     Heater_Off();
}
/******************************************************************************/
static void Heater_On(void){
       GPIO_SetPinValue(HEATER_PORT_ID, HEATER_PIN_ID, HEATER_STATE_ON);
}
/******************************************************************************/
static void Heater_Off(void){
       GPIO_SetPinValue(HEATER_PORT_ID, HEATER_PIN_ID, HEATER_STATE_OFF);
}
/******************************************************************************/
void HEATER_Set(const u8_t REQ_TMP, const u8_t AVG_TMP, const Bool_t UPDATE_ENABLE){
    Tmp_Req = REQ_TMP;
    Tmp_Avg = AVG_TMP;
    Update = UPDATE_ENABLE;
}
/******************************************************************************/
void HEATER_Update(void){
     HEATER_Update_Mode();
     if(TRUE == Update){
        switch(HEATER_Mode){
                case HEATER_MODE_POWER_OFF:
                     Heater_Off();
                     LED_Set_Mode(LED_MODE_OFF, TRUE);
                     break;
                case HEATER_MODE_OFF:
                     Heater_Off();
                     LED_Set_Mode(LED_MODE_OFF, TRUE);
                     break;
                case HEATER_MODE_ON:
                     Heater_On();
                     LED_Set_Mode(LED_MODE_BLINKING, TRUE);
                     break;
        }
        Update = FALSE;
     }
}
/******************************************************************************/
static void HEATER_Update_Mode(void){
       s8_t Diff = 0;
       Diff = Tmp_Req - Tmp_Avg;
       if(TRUE == SW_Period_Is_Ended()){
          switch(HEATER_Mode){
                 case HEATER_MODE_POWER_OFF:
                      if(SW_STATE_ON == SW_Read(SW_POWER)){
                         HEATER_Mode = HEATER_MODE_OFF;
                      }
                      else{
                         Heater_Off(); /* At sny time sw power pressed */
                         LED_Set_Mode(LED_MODE_OFF, TRUE);
                      }
                      break;
                 case HEATER_MODE_OFF:
                 case HEATER_MODE_ON:
                      if(SW_STATE_ON == SW_Read(SW_POWER)){
                         HEATER_Mode = HEATER_MODE_POWER_OFF;
                         LED_Set_Mode(LED_MODE_OFF, TRUE);
                      }
                      break;
                 default:
                      /* Error: Undefined HEATER_MODE */
                      break;
          }
       }
       if(TRUE == Update){
          switch(HEATER_Mode){
                  case HEATER_MODE_POWER_OFF:
                       /* Do Nothung */
                       break;
                  case HEATER_MODE_OFF:
                       if(Diff >= 5){
                          HEATER_Mode = HEATER_MODE_ON;
                       }
                       break;
                  case HEATER_MODE_ON:
                       if(Tmp_Req <= Tmp_Avg){
                          HEATER_Mode = HEATER_MODE_OFF;
                       }
                       break;
          }

     }
}
/******************************************************************************/
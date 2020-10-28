/******************************************************************************/
#ifndef COOLER_H
#include "COOLER.h"
#endif
/******************************************************************************/
typedef enum{
        COOLER_MODE_POWER_OFF = 0,
        COOLER_MODE_OFF,
        COOLER_MODE_ON
}COOLER_MODE_t;
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
/******************************************************************************/
void COOLER_Set(const u8_t REQ_TMP, const u8_t AVG_TMP, const Bool_t UPDATE_ENABLE);
static void COOLER_On(void);
static void COOLER_Off(void);
static void COOLER_Update_Mode(void);
extern Bool_t SW_Period_Is_Ended(void);
SW_State_t SW_Read(const SW_t SW_ID);
void LED_Set_Mode(const LED_MODE_t MODE, const Bool_t LED_UPDATE_ENABLE);
/******************************************************************************/
static s8_t Tmp_Req = 0, Tmp_Avg = 0;
static Bool_t Update = FALSE;
static COOLER_MODE_t COOLER_Mode = COOLER_MODE_POWER_OFF;
/******************************************************************************/
void COOLER_Init(void){
     GPIO_SetPinDirection(COOLER_PORT_ID, COOLER_PIN_ID, COOLER_DIRECTION_ID);
     COOLER_Off();
}
/******************************************************************************/
static void COOLER_On(void){
       GPIO_SetPinValue(COOLER_PORT_ID, COOLER_PIN_ID, COOLER_STATE_ON);
}
/******************************************************************************/
static void COOLER_Off(void){
       GPIO_SetPinValue(COOLER_PORT_ID, COOLER_PIN_ID, COOLER_STATE_OFF);
}
/******************************************************************************/
void COOLER_Set(const u8_t REQ_TMP, const u8_t AVG_TMP, const Bool_t UPDATE_ENABLE){
    Tmp_Req = REQ_TMP;
    Tmp_Avg = AVG_TMP;
    Update = UPDATE_ENABLE;
}
/******************************************************************************/
void COOLER_Update(void){
     COOLER_Update_Mode();
     if(TRUE == Update){
        switch(COOLER_Mode){
                case COOLER_MODE_POWER_OFF:
                     COOLER_Off();
                     LED_Set_Mode(LED_MODE_OFF, TRUE);
                     break;
                case COOLER_MODE_OFF:
                     COOLER_Off();
                    // LED_Set_Mode(LED_MODE_OFF, TRUE);
                     break;
                case COOLER_MODE_ON:
                     COOLER_On();
                     LED_Set_Mode(LED_MODE_ON, TRUE);
                     break;
        }
        Update = FALSE;
     }
}
/******************************************************************************/
static void COOLER_Update_Mode(void){
       s8_t Diff = 0;
       Diff = Tmp_Avg - Tmp_Req;
       if(TRUE == SW_Period_Is_Ended()){
          switch(COOLER_Mode){
                 case COOLER_MODE_POWER_OFF:
                      if(SW_STATE_ON == SW_Read(SW_POWER)){
                         COOLER_Mode = COOLER_MODE_OFF;
                      }
                      else{
                         COOLER_Off(); /* AT sny time sw power pressed */
                         LED_Set_Mode(LED_MODE_OFF, TRUE);
                      }
                      break;
                 case COOLER_MODE_OFF:
                 case COOLER_MODE_ON:
                      if(SW_STATE_ON == SW_Read(SW_POWER)){
                         COOLER_Mode = COOLER_MODE_POWER_OFF;
                         LED_Set_Mode(LED_MODE_OFF, TRUE);
                      }
                      break;
                 default:
                      /* Error: Undefined COOLER_MODE */
                      break;
          }
       }
       if(TRUE == Update){
        switch(COOLER_Mode){
                case COOLER_MODE_POWER_OFF:
                     /* Do Nothung */
                     break;
                case COOLER_MODE_OFF:
                     if(Diff >= 5){
                        COOLER_Mode = COOLER_MODE_ON;
                     }
                     break;
                case COOLER_MODE_ON:
                     if(Tmp_Avg <= Tmp_Req){
                        COOLER_Mode = COOLER_MODE_OFF;
                     }
                     break;
        }

     }
}
/******************************************************************************/
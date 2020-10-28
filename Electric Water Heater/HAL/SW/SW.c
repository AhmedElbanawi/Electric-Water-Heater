/******************************************************************************/
#ifndef SW_H
#include "SW.h"
#endif
/******************************************************************************/
#define SW_PERIOD_20_MS 4
#define ENDED 0
/******************************************************************************/
typedef enum{ 
        SW_RELEASED = 0,
        SW_PRESSED
}SW_TIME_t;
/******************************************************************************/
static void SW_Update_State(const SW_t SW_ID);
static void SW_Update_Period(void);
/******************************************************************************/
Bool_t SW_Period_Is_Ended(void);
SW_State_t SW_Read(const SW_t SW_ID);
/******************************************************************************/
static SW_STATE_t SW_State[SW_MAX_NUMBER] = { SW_STATE_OFF };
static Bool_t SW_Period_Ended = FALSE;
/******************************************************************************/
void SW_Init(void){
     GPIO_SetPinDirection(SW_POWER_PORT_ID, SW_POWER_PIN_ID, SW_DIRECTION_ID);
     GPIO_SetPinDirection(SW_UP_PORT_ID, SW_UP_PIN_ID, SW_DIRECTION_ID);
     GPIO_SetPinDirection(SW_DOWN_PORT_ID, SW_DOWN_PIN_ID, SW_DIRECTION_ID);
}
/******************************************************************************/
static void SW_Update_State(const SW_t SW_ID){
       static SW_TIME_t SW_Time[SW_MAX_NUMBER] = { SW_RELEASED };
       switch(SW_ID){
              case SW_POWER:
                   switch(SW_Time[SW_POWER]){
                          case SW_RELEASED:
                               SW_State[SW_POWER] = SW_STATE_OFF;
                               if(GPIO_LOW == GPIO_ReadPinValue(SW_POWER_PORT_ID, SW_POWER_PIN_ID)){
                                  SW_Time[SW_POWER] = SW_PRESSED;
                               }
                               break;
                          case SW_PRESSED:
                               if(GPIO_HIGH == GPIO_ReadPinValue(SW_POWER_PORT_ID, SW_POWER_PIN_ID)){
                                  SW_Time[SW_POWER] = SW_RELEASED;
                                  SW_State[SW_POWER] = SW_STATE_ON;
                               }
                               break;
                          default:
                               /* Error: Undefined SW_TIME_STATE */
                               break;
                   }
                   break;
              case SW_UP:
                   switch(SW_Time[SW_UP]){
                          case SW_RELEASED:
                               SW_State[SW_UP] = SW_STATE_OFF;
                               if(GPIO_LOW == GPIO_ReadPinValue(SW_UP_PORT_ID, SW_UP_PIN_ID)){
                                  SW_Time[SW_UP] = SW_PRESSED;
                               }
                               break;
                          case SW_PRESSED:
                               if(GPIO_HIGH == GPIO_ReadPinValue(SW_UP_PORT_ID, SW_UP_PIN_ID)){
                                  SW_Time[SW_UP] = SW_RELEASED;
                                  SW_State[SW_UP] = SW_STATE_ON;
                               }
                               break;
                          default:
                               /* Error: Undefined SW_TIME_STATE */
                               break;
                   }
                   break;
              case SW_DOWN:
                   switch(SW_Time[SW_DOWN]){
                          case SW_RELEASED:
                               SW_State[SW_DOWN] = SW_STATE_OFF;
                               if(GPIO_LOW == GPIO_ReadPinValue(SW_DOWN_PORT_ID, SW_DOWN_PIN_ID)){
                                  SW_Time[SW_DOWN] = SW_PRESSED;
                               }
                               break;
                          case SW_PRESSED:
                               if(GPIO_HIGH == GPIO_ReadPinValue(SW_DOWN_PORT_ID, SW_DOWN_PIN_ID)){
                                  SW_Time[SW_DOWN] = SW_RELEASED;
                                  SW_State[SW_DOWN] = SW_STATE_ON;
                               }
                               break;
                          default:
                               /* Error: Undefined SW_TIME_STATE */
                               break;
                   }
                   break;
              default:
                   /* Error: Undefined SW_ID */
                   break;
       }
}
/******************************************************************************/
SW_State_t SW_Read(const SW_t SW_ID){
           SW_State_t SW_Reading = SW_STATE_OFF;
           switch(SW_ID){
                  case SW_POWER:
                       SW_Reading = SW_State[SW_POWER];
                       break;
                  case SW_UP:
                       SW_Reading = SW_State[SW_UP];
                       break;
                  case SW_DOWN:
                       SW_Reading = SW_State[SW_DOWN];
                       break;
                  default:
                       /* Error: Undefined SW_ID */
                       break;
           }
           return SW_Reading;
}
/******************************************************************************/
Bool_t SW_Period_Is_Ended(void){
       return FALSE == SW_Period_Ended ? FALSE : TRUE;
}
/******************************************************************************/
static void SW_Update_Period(void){
       static u8_t SW_Period_Ms = SW_PERIOD_20_MS;
       SW_Period_Ended = FALSE;
       SW_Period_Ms--;
       if(ENDED == SW_Period_Ms){
          SW_Period_Ms = SW_PERIOD_20_MS;
          SW_Period_Ended = TRUE;
       }
}
/******************************************************************************/
void SW_Update(void){
     SW_Update_Period();
     if(TRUE == SW_Period_Ended){
        SW_Update_State(SW_POWER);
        SW_Update_State(SW_UP);
        SW_Update_State(SW_DOWN);
     }
}
/******************************************************************************/
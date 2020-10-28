/******************************************************************************/
#ifndef SSD_H
#include "SSD.h"
#endif
/******************************************************************************/
#define ENDED 0
#define SSD_BLINKING_PERIOD 5
#define SSD_BLINKING_OFF_PERIOD 200
#define SSD_BLINKING_ON_PERIOD 200
/******************************************************************************/
typedef enum{
        SSD_TENS = 0,
        SSD_ONES
}SSD_t;
typedef enum{
        SSD_MODE_OFF = 0,
        SSD_MODE_ON,
        SSD_MODE_BLINKING_OFF,
        SSD_MODE_BLINKING_ON
}SSD_MODE_t;
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
/******************************************************************************/
static void SSD_On(const SSD_t SSD_ID);
static void SSD_Off(const SSD_t SSD_ID);
static void SSD_Update_Symbol(const u8_t SSD_SYMBOL);
static void SSD_Refesh(void);
static void SSD_Update_Mode(void);
extern Bool_t SW_Period_Is_Ended(void);
extern SW_State_t SW_Read(const SW_t SW_ID);
void SSD_Set_Symbol(const u8_t SYMBOL);
/******************************************************************************/
static u8_t SSD_Symbol = 0,
            SSD_Blinking_Period = SSD_BLINKING_PERIOD,
            SSD_Blinking_On_Period = SSD_BLINKING_ON_PERIOD,
            SSD_Blinking_Off_Period = SSD_BLINKING_OFF_PERIOD;
                            
static SSD_MODE_t SSD_Mode = SSD_MODE_OFF;
/******************************************************************************/
void SSD_Init(void){
                    /* Init Data Lines */
     GPIO_SetPinDirection(SSD_A_PORT_ID, SSD_A_PIN_ID, SSD_DIRECTION_ID);
     GPIO_SetPinDirection(SSD_B_PORT_ID, SSD_B_PIN_ID, SSD_DIRECTION_ID);
     GPIO_SetPinDirection(SSD_C_PORT_ID, SSD_C_PIN_ID, SSD_DIRECTION_ID);
     GPIO_SetPinDirection(SSD_D_PORT_ID, SSD_D_PIN_ID, SSD_DIRECTION_ID);
                    /* Init Control Lines */
     GPIO_SetPinDirection(SSD_TENS_PORT_ID, SSD_TENS_PIN_ID, SSD_DIRECTION_ID);
     GPIO_SetPinDirection(SSD_ONES_PORT_ID, SSD_ONES_PIN_ID, SSD_DIRECTION_ID);
}
/******************************************************************************/
static void SSD_On(const SSD_t SSD_ID){
       switch(SSD_ID){
              case SSD_TENS:
                   GPIO_SetPinValue(SSD_TENS_PORT_ID, SSD_TENS_PIN_ID, SSD_STATE_ON);
                   break;
              case SSD_ONES:
                   GPIO_SetPinValue(SSD_ONES_PORT_ID, SSD_ONES_PIN_ID, SSD_STATE_ON);
                   break;
              default:
                   /* Error: Undefined SSD */
                   break;
       }
} 
/******************************************************************************/
static void SSD_Off(const SSD_t SSD_ID){
       switch(SSD_ID){
              case SSD_TENS:
                   GPIO_SetPinValue(SSD_TENS_PORT_ID, SSD_TENS_PIN_ID, SSD_STATE_OFF);
                   break;
              case SSD_ONES:
                   GPIO_SetPinValue(SSD_ONES_PORT_ID, SSD_ONES_PIN_ID, SSD_STATE_OFF);
                   break;
              default:
                   /* Error: Undefined SSD */
                   break;
       }
}
/******************************************************************************/
static void SSD_Update_Symbol(const u8_t SSD_SYMBOL){
       GPIO_SetPinValue(SSD_A_PORT_ID, SSD_A_PIN_ID, GET_BIT(SSD_SYMBOL, 0));
       GPIO_SetPinValue(SSD_B_PORT_ID, SSD_B_PIN_ID, GET_BIT(SSD_SYMBOL, 1));
       GPIO_SetPinValue(SSD_C_PORT_ID, SSD_C_PIN_ID, GET_BIT(SSD_SYMBOL, 2));
       GPIO_SetPinValue(SSD_D_PORT_ID, SSD_D_PIN_ID, GET_BIT(SSD_SYMBOL, 3));
}
/******************************************************************************/
static void SSD_Refesh(void){
       static SSD_t SSD_Id = SSD_TENS;
       SSD_Off(SSD_TENS);
       SSD_Off(SSD_ONES);
       switch(SSD_Id){
              case SSD_TENS:
                   SSD_Update_Symbol(SSD_Symbol / 10);
                   SSD_On(SSD_TENS);
                   SSD_Id = SSD_ONES;
                   break;
              case SSD_ONES:
                   SSD_Update_Symbol(SSD_Symbol % 10);
                   SSD_On(SSD_ONES);
                   SSD_Id = SSD_TENS;
                   break;
              default:
                   /* Error: Undefined SSD */
                   break;
       }
}
/******************************************************************************/
void SSD_Update(void){
     SSD_Update_Mode();
     switch(SSD_Mode){
            case SSD_MODE_ON:
                 SSD_Refesh();
                 break;
            case SSD_MODE_OFF:
                 SSD_Off(SSD_TENS);
                 SSD_Off(SSD_ONES);
                 break;
            case SSD_MODE_BLINKING_OFF:
                 SSD_Off(SSD_TENS);
                 SSD_Off(SSD_ONES);
                 SSD_Blinking_Off_Period--;
                 if(ENDED == SSD_Blinking_Off_Period){
                    SSD_Blinking_Period--;
                    SSD_Blinking_Off_Period = SSD_BLINKING_OFF_PERIOD;
                    if(ENDED == SSD_Blinking_Period){
                       SSD_Blinking_Period = SSD_BLINKING_PERIOD;
                       SSD_Mode = SSD_MODE_ON;
                    }
                    else{
                       SSD_Mode = SSD_MODE_BLINKING_ON;
                    }
                 }
                 break;
            case SSD_MODE_BLINKING_ON:
                 SSD_Refesh();
                 SSD_Blinking_On_Period--;
                 if(ENDED == SSD_Blinking_On_Period){
                    SSD_Blinking_Period--;
                    SSD_Blinking_On_Period = SSD_BLINKING_ON_PERIOD;
                    if(ENDED == SSD_Blinking_Period){
                       SSD_Blinking_Period = SSD_BLINKING_PERIOD;
                       SSD_Mode = SSD_MODE_ON;
                    }
                    else{
                       SSD_Mode = SSD_MODE_BLINKING_OFF;
                    }
                 }
                 break;
            default:
                 /* Erorr: Undefined SSD_MODE */
                 break;
     }
}
/******************************************************************************/
static void SSD_Update_Mode(void){
       if(TRUE == SW_Period_Is_Ended()){
          if(SW_STATE_ON == SW_Read(SW_POWER)){
             switch(SSD_Mode){
                    case SSD_MODE_ON:
                    case SSD_MODE_BLINKING_OFF:
                    case SSD_MODE_BLINKING_ON:
                         SSD_Mode = SSD_MODE_OFF;
                         break;
                    case SSD_MODE_OFF:
                         SSD_Mode = SSD_MODE_ON;
                         break;
                    default:
                         /* Erorr: Undefined SSD_MODE */
                         break;
             }
          }
          else if(SW_STATE_ON == SW_Read(SW_UP) || SW_STATE_ON == SW_Read(SW_DOWN)){
             switch(SSD_Mode){
                    case SSD_MODE_ON:
                    case SSD_MODE_BLINKING_ON:
                         SSD_Mode = SSD_MODE_BLINKING_OFF;
                         SSD_Blinking_Period = SSD_BLINKING_PERIOD;
                         SSD_Blinking_On_Period = SSD_BLINKING_ON_PERIOD;
                         SSD_Blinking_Off_Period = SSD_BLINKING_OFF_PERIOD;
                         break;
                    case SSD_MODE_BLINKING_OFF:
                         SSD_Mode = SSD_MODE_BLINKING_ON;
                         SSD_Blinking_Period = SSD_BLINKING_PERIOD;
                         SSD_Blinking_On_Period = SSD_BLINKING_ON_PERIOD;
                         SSD_Blinking_Off_Period = SSD_BLINKING_OFF_PERIOD;
                         break;
                    case SSD_MODE_OFF:
                         /* Do Nothing */
                         break;
                    default:
                         /* Erorr: Undefined SSD_MODE */
                         break;
             }
          }
       }
}
/******************************************************************************/
void SSD_Set_Symbol(const u8_t SYMBOL){
     SSD_Symbol = SYMBOL;
}
/******************************************************************************/
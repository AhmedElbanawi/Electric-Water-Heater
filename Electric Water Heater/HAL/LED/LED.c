/******************************************************************************/
#ifndef LED_H
#include "LED.h"
#endif
/******************************************************************************/
typedef enum{
        LED_MODE_OFF = 0,
        LED_MODE_ON,
        LED_MODE_BLINKING
}LED_MODE_t;
/******************************************************************************/
static void LED_On(void);
static void LED_Off(void);
static void LED_Blink(void);
void LED_Set_Mode(const LED_MODE_t MODE, const Bool_t LED_UPDATE_ENABLE);
/******************************************************************************/
static LED_STATE_t LED_State = LED_STATE_OFF;
static LED_MODE_t LED_Mode = LED_MODE_OFF;
static Bool_t Update = FALSE;
/******************************************************************************/
void LED_Init(void){
            /* Define Required Pin as Output For The Heater Led */
       GPIO_SetPinDirection(LED_PORT_ID, LED_PIN_ID, LED_PIN_DIRECTION_ID);
       LED_Off();
}
static void LED_On(void){
          /* Heater Led is On */
     GPIO_SetPinValue(LED_PORT_ID, LED_PIN_ID, LED_STATE_ON);
     LED_State = LED_STATE_ON;  /* Heater Led State is On */
}
static void LED_Off(void){
              /* Heater Led is Off */
     GPIO_SetPinValue(LED_PORT_ID, LED_PIN_ID, LED_STATE_OFF);
     LED_State = LED_STATE_OFF;  /* Heater Led State is Off */
}
static void LED_Blink(void){
     if(LED_STATE_ON == LED_State){
        LED_Off(); /* Heater Led is Off */
     }
     else{
        LED_On();  /* Heater Led is On */
     }
}
void LED_Update(void){
     if(TRUE == Update){
        switch(LED_Mode){
               case LED_MODE_OFF:
                    LED_Off();
                    break;
               case LED_MODE_ON:
                    LED_On();
                    break;
               case LED_MODE_BLINKING:
                    LED_Blink();
                    break;
               default:
                    /* Error: Undefined LED_MODE */
                    break;
        }
        Update = FALSE;
     }

}
void LED_Set_Mode(const LED_MODE_t MODE, const Bool_t LED_UPDATE_ENABLE){
     LED_Mode = MODE;
     Update = LED_UPDATE_ENABLE;
}
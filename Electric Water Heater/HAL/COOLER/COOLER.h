/******************************************************************************/
#ifndef COOLER_H
#define COOLER_H
#endif
/******************************************************************************/
#ifndef GPIO_H
#include "GPIO.h"
#endif
/******************************************************************************/
typedef enum{
        COOLER_PIN_ID = GPIO_PIN1,
        COOLER_PORT_ID = GPIO_PORTC
}COOLER_ID_t;
typedef enum{
        COOLER_DIRECTION_ID = GPIO_OUTPUT
}COOLER_DIRECTION_ID_t;
typedef enum{
        COOLER_STATE_OFF = 0,
        COOLER_STATE_ON
}COOLER_STATE_t;
/******************************************************************************/
void COOLER_Init(void);
void COOLER_Update(void);
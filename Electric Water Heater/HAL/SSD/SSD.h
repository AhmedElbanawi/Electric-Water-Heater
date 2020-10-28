/******************************************************************************/
#ifndef SSD_H
#define SSD_H
#endif
/******************************************************************************/
#ifndef GPIO_H
#include "GPIO.h"
#endif
/******************************************************************************/
typedef enum{
        SSD_A_PIN_ID = GPIO_PIN0,
        SSD_B_PIN_ID = GPIO_PIN1,
        SSD_C_PIN_ID = GPIO_PIN2,
        SSD_D_PIN_ID = GPIO_PIN3,
        SSD_TENS_PIN_ID = GPIO_PIN4,
        SSD_ONES_PIN_ID = GPIO_PIN5
}SSD_PIN_ID_t;
typedef enum{
        SSD_DIRECTION_ID = GPIO_OUTPUT
}SSD_DIRECTION_t;
typedef enum{
        SSD_A_PORT_ID = GPIO_PORTB,
        SSD_B_PORT_ID = GPIO_PORTB,
        SSD_C_PORT_ID = GPIO_PORTB,
        SSD_D_PORT_ID = GPIO_PORTB,
        SSD_TENS_PORT_ID = GPIO_PORTB,
        SSD_ONES_PORT_ID = GPIO_PORTB
}SSD_PORT_ID_t;
typedef enum{
        SSD_STATE_ON = 0,
        SSD_STATE_OFF
}SSD_STATE_t;
/******************************************************************************/
void SSD_Init(void);
void SSD_Update(void);
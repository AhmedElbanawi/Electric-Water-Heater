/******************************************************************************/
#ifndef SW_H
#define SW_H
#endif
/******************************************************************************/
#ifndef GPIO_H
#include "GPIO.h"
#endif
/******************************************************************************/
typedef enum{ 
        SW_POWER_PIN_ID = GPIO_PIN0,
        SW_UP_PIN_ID = GPIO_PIN1,
        SW_DOWN_PIN_ID = GPIO_PIN2
}SW_PIN_ID_t;
typedef enum{
        SW_POWER_PORT_ID = GPIO_PORTD,
        SW_UP_PORT_ID = GPIO_PORTD,
        SW_DOWN_PORT_ID = GPIO_PORTD
}SW_PORT_ID_t;
typedef enum{ 
        SW_DIRECTION_ID = GPIO_INPUT
}SW_DIRECTION_t;
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
void SW_Init(void);
void SW_Update(void);
/******************************************************************************/
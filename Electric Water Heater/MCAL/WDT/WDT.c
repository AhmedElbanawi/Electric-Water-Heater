/******************************************************************************/
#ifndef WDT_H
#include "WDT.h"
#endif
/******************************************************************************/
void WDT_SetPeriode(const WDT_Periode_t WDT_PERIODE){
     SET_BIT(OPTION_REG, 3);                /* Assign Prescaler To WDT */
     OPTION_REG &= 0XF8;                    /* Inite WDT Prescaler */
     OPTION_REG |= WDT_PERIODE;             /* Assign The Reguired Prescaler */
}
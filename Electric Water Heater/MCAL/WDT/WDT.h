/******************************************************************************/
#ifndef WDT_H
#define WDT_H
#endif
/******************************************************************************/
#ifndef BIT_MANIPULATION_H
#include "Bit_Manipulation.h"
#endif
/******************************************************************************/
typedef enum{
        WDT_PERIODE_18_MS = 0,
        WDT_PERIODE_36_MS,
        WDT_PERIODE_72_MS,
        WDT_PERIODE_144_MS,
        WDT_PERIODE_288_MS,
        WDT_PERIODE_576_MS,
        WDT_PERIODE_1152_MS,
        WDT_PERIODE_2304_MS
}WDT_Periode_t;
void WDT_SetPeriode(const WDT_Periode_t WDT_PERIODE);
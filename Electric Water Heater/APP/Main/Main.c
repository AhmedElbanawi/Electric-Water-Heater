/******************************************************************************/
#ifndef SW_H
#include "SW.h"
#endif
/******************************************************************************/
#ifndef SSD_H
#include "SSD.h"
#endif
/******************************************************************************/
#ifndef TMP_SENSOR_H
#include "TMP_SENSOR.h"
#endif
/******************************************************************************/
#ifndef TMP_H
#include "TMP.h"
#endif
/******************************************************************************/
#ifndef HEATER_H
#include "HEATER.h"
#endif
/******************************************************************************/
#ifndef COOLER_H
#include "COOLER.h"
#endif
/******************************************************************************/
#ifndef LED_H
#include "LED.h"
#endif
/******************************************************************************/
#ifndef EEPROM_H
#include "EEPROM.h"
#endif
/******************************************************************************/
#ifndef OS_H
#include "OS.h"
#endif
/******************************************************************************/
extern u8_t TMP_Required;
/******************************************************************************/
void main() {
     OS_Tick_Init(); /* Tick = 5 ms */
     EEPROM_Init(100000); /* Baud Rate 100 KHZ */
     TMP_Required = EEPROM_Read_Byte(EEPROM_ID_1, 0X00);
     SW_Init();
     SSD_Init();
     TMP_SENSOR_Init();
     HEATER_Init();
     COOLER_Init();
     LED_Init();
     while(1){
              if(TRUE == OS_Update){
                 SW_Update();         /* Every 20 ms */
                 TMP_SENSOR_Update(); /* Every 100 ms */
                 TMP_Update();        /* REQ TMP Every 20 ms and AVG TMP Every 1000 ms */
                 SSD_Update();        /* Every 5 ms */
                 HEATER_Update();     /* Every 1000 ms */
                 COOLER_Update();     /* Every 1000 ms */
                 LED_Update();        /* Every 1000 ms */
                 EEPROM_Update();     /* Every 20 ms */
                 OS_Update = FALSE;
              }
     }

}
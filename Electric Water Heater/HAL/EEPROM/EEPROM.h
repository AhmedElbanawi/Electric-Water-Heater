/******************************************************************************/
#ifndef EEPROM_H
#define EEPROM_H
#endif
/******************************************************************************/
#ifndef SYS_DATA_TYPES_H
#include "Sys_Data_Types.h"
#endif
/******************************************************************************/
#define EEPROM_BASE_ADDRESS 1010000
/******************************************************************************/
typedef enum{
        EEPROM_ID_1 = 0,
        EEPROM_ID_2,
        EEPROM_ID_3,
        EEPROM_ID_4,
        EEPROM_ID_5,
        EEPROM_ID_6,
        EEPROM_ID_7,
        EEPROM_ID_8
}EEPROM_ID_t;
void EEPROM_Init(const u32_t BAUDRATE);
u8_t EEPROM_Read_Byte(const EEPROM_ID_t EEPROM_ID, const u8_t EEPROM_ADDRESS);
void EEPROM_Update(void);
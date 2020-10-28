/******************************************************************************/
#ifndef I2C_H
#include "I2C.h"
#endif
/******************************************************************************/
#ifndef EEPROM_H
#include "EEPROM.h"
#endif
/******************************************************************************/
static void EEPROM_Write_Byte(const EEPROM_ID_t EEPROM_ID,
                              const u8_t EEPROM_ADDRESS,
                              const u8_t DATA);
void EEPROM_Store(const u8_t DATA, const Bool_t UPDATE_ENABLE);
/******************************************************************************/
static Bool_t Update = FALSE;
static u8_t EEPROM_Data = 0;
/******************************************************************************/
void EEPROM_Init(const u32_t BAUDRATE){
     I2C_Master_Init(BAUDRATE);
}
void EEPROM_Write_Byte(const EEPROM_ID_t EEPROM_ID,
                       const u8_t EEPROM_ADDRESS,
                       const u8_t DATA){
     I2C_Start();
     while( I2C_Write_Byte((EEPROM_BASE_ADDRESS | EEPROM_ID) << 1) );
     while( I2C_Write_Byte(EEPROM_ADDRESS) );
     while( I2C_Write_Byte(DATA) );
     I2C_Stop();
}
u8_t EEPROM_Read_Byte(const EEPROM_ID_t EEPROM_ID, const u8_t EEPROM_ADDRESS){
     u8_t Data;
     I2C_Start();
     while( I2C_Write_Byte((EEPROM_BASE_ADDRESS | EEPROM_ID) << 1) );
     while( I2C_Write_Byte(EEPROM_ADDRESS) );
     I2C_ReStart();
     while( I2C_Write_Byte( ( (EEPROM_BASE_ADDRESS | EEPROM_ID) << 1) | 0X01 ) );
     Data = I2C_Read_Byte();
     I2C_Stop();
     return Data;
}
void EEPROM_Update(void){
     if(TRUE == Update){
       EEPROM_Write_Byte(EEPROM_ID_1, 0X00, EEPROM_Data);
       Update = FALSE;
     }
}
void EEPROM_Store(const u8_t DATA, const Bool_t UPDATE_ENABLE){
     Update = UPDATE_ENABLE;
     EEPROM_Data = DATA;
}
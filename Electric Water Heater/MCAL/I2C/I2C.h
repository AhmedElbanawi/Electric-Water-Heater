/******************************************************************************/
#ifndef I2C_H
#define I2C_H
#endif
/******************************************************************************/
#ifndef SYS_DATA_TYPES_H
#include "Sys_Data_Types.h"
#endif
/******************************************************************************/
#ifndef BIT_MANIPULATION_H
#include "Bit_Manipulation.h"
#endif
/******************************************************************************/
#define FOSC 4000000
/******************************************************************************/
void I2C_Wait(void);
void I2C_Master_Init(const u32_t BAUDRATE);
void I2C_Start(void);
void I2C_ReStart(void);
void I2C_Stop(void);
void I2C_ACK(void);
void I2C_NACK(void);
u8_t I2C_Write_Byte(const u8_t DATA);
u8_t I2C_Read_Byte(void);
/******************************************************************************/
#ifndef I2C_H
#include "I2C.h"
#endif
/******************************************************************************/
void I2C_Wait(void){
     /* Wait Untill The Bus Return To Idle State */
     while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
void I2C_Master_Init(const u32_t BAUDRATE){
        /* Enable Serial Port and Define SDA, SCL as a Serial Port Pins,
          Enable Defining BaudRate Mode
         */
     SSPCON = 0X28;
        /* Start, Restart, Stop and Acknowledge Condition are Idle */
     SSPCON2 = 0x00;
     SSPSTAT = 0x00;
     SSPADD = ( (FOSC / 4) / BAUDRATE ) - 1; /* Define BaudRate */
            /* Enable Open Drain Mode */
     SET_BIT(TRISC, 3);
     SET_BIT(TRISC, 4);
}
void I2C_Start(void){
     I2C_Wait();
     SET_BIT(SSPCON2, 0); /* Start Condition */
}
void I2C_ReStart(void){
     I2C_Wait();
     SET_BIT(SSPCON2, 1); /* ReStart Condition */
}
void I2C_Stop(void){
     I2C_Wait();
     SET_BIT(SSPCON2, 2); /* Stop Condition */
}
void I2C_ACK(void){
     I2C_Wait();
     CLEAR_BIT(SSPCON2, 5); /* ACK */
     SET_BIT(SSPCON2, 4);   /* Enable */
}
void I2C_NACK(void){
     I2C_Wait();
     SET_BIT(SSPCON2, 5);   /* NACK */
     SET_BIT(SSPCON2, 4);   /* Enable */
}
u8_t I2C_Write_Byte(const u8_t DATA){
     I2C_Wait();
     SSPBUF = DATA;      /* Send Data */
     I2C_Wait();
     return GET_BIT(SSPCON2, 6); /* Get ACK State */
}
u8_t I2C_Read_Byte(void){
     I2C_Wait();
     SET_BIT(SSPCON2, 3);       /* Enable Receive */
     I2C_Wait();
     while(!GET_BIT(PIR1, 3));  /* Check Rx Flag */
     CLEAR_BIT(PIR1, 3);        /* Clear Rx Flag */
     return SSPBUF;             /* Return Data */
}
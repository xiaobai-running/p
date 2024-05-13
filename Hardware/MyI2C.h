#ifndef _MYI2C_H_
#define _MYI2C_H_

#include "stm32f10x.h"
#include "stdint.h"
#include "Delay.h"

uint8_t MyI2C_ReceiveACK(void);
void MyI2C_SendACK(uint8_t AckBit);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendByte(uint8_t Byte);
void MyI2C_Stop(void);
void MyI2C_Start(void);
void MyI2C_Init(void);

#endif

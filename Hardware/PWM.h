#ifndef _PWM_H_
#define _PWM_H_

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include <stdint.h>

void PWM_GPIO_Init(void);     //��ʼ��GPIO
void PWM_Init(uint16_t arr, uint16_t psc);          //��ʼ��PWM


#endif

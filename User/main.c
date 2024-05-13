#include "main.h"

// Cycle time is 1ms, duty cycle is PWM_Compare_Value/PWM_Period_Value

uint16_t PWM1_Compare_Value = 0;
uint16_t PWM2_Compare_Value = 0;
uint16_t PWM3_Compare_Value = 0;
uint16_t PWM4_Compare_Value = 0;


int main(void)
{
	OLED_Init();                         // Initialize OLED
	OLED_Clear();                        // Clear OLED
	OLED_ShowString(4,1,"Hello World!"); // Display "Hello World!" on OLED

	PWM_GPIO_Init();                     	 	 	// Initialize PWM GPIO
	PWM_Init(1000, 72);                 		 	// Initialize PWM and set cycle time is 1ms

	TIM_SetCompare2(TIM2, PWM2_Compare_Value);   	// Set PWM duty cycle to 50%
	TIM_SetCompare3(TIM3, PWM3_Compare_Value);
	TIM_SetCompare2(TIM4, PWM4_Compare_Value);
	TIM_SetCompare1(TIM1, PWM1_Compare_Value);
	while(1)
	{
		OLED_ShowString(4,1,"Hello World!"); // Display "Hello World!" on OLED
	}
}



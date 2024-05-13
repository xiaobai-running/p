#include "PWM.h"

//PWM1 CH1��CH1N
#define PWM1_GPIO_Port          GPIOA
#define PWM1_Pin                GPIO_Pin_8
#define PWM1N_GPIO_Port         GPIOB
#define PWM1N_Pin               GPIO_Pin_13

//PWM2 CH2
#define PWM2_GPIO_Port          GPIOA
#define PWM2_Pin                GPIO_Pin_1

//PWM3 CH3
#define PWM3_GPIO_Port          GPIOB
#define PWM3_Pin                GPIO_Pin_0

//PWM4 CH4
#define PWM4_GPIO_Port          GPIOB
#define PWM4_Pin                GPIO_Pin_7


void PWM_GPIO_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin     = PWM1_Pin | PWM2_Pin;
    GPIO_Init(PWM1_GPIO_Port, &GPIO_InitStructure);     //A1,A8

    GPIO_InitStructure.GPIO_Pin     = PWM1N_Pin | PWM3_Pin | PWM4_Pin;
    GPIO_Init(PWM1N_GPIO_Port, &GPIO_InitStructure);    //B13,B0,B7
}

void PWM_Init(uint16_t arr, uint16_t psc)
{
    //��ʼ����ʱ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    PWM_GPIO_Init();    //��ʼ��PWM�������

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;

    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period            = arr-1;    //�Զ���װ��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler         = psc-1;    //��Ƶϵ��
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);    //PWM1 CH1��CH1N
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);    //PWM2 CH2
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);    //PWM3 CH3
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);    //PWM4 CH2

    //ͨ�ö�ʱ��
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = 0;    //��ʼռ�ձ�
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);    //PWM2 CH2
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);    //PWM3 CH3
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);    //PWM4 CH2

    TIM_Cmd(TIM2, ENABLE);    //PWM2 CH2
    TIM_Cmd(TIM3, ENABLE);    //PWM3 CH3
    TIM_Cmd(TIM4, ENABLE);    //PWM4 CH2

    //�߼���ʱ��
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OCInitStructure.TIM_Pulse        = 0;    //��ʼռ�ձ�
    TIM_OC1Init(TIM1,  &TIM_OCInitStructure);    //PWM1 CH1

    TIM_Cmd(TIM1, ENABLE);    //PWM1 CH1��CH1N
    TIM_CtrlPWMOutputs(TIM1, ENABLE);    //ʹ��PWM1���
}

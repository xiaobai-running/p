#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"
#include "stdint.h"

#define KEY_FIFO_SIZE 16  //��ֵ��������С

typedef struct
{
    uint8_t Buf[KEY_FIFO_SIZE];    //��ֵ������
    uint8_t Read;                  //��������ָ��
    uint8_t Write;                 //������дָ��
}KEY_FIFO_T;

typedef enum
{
    KEY_NONE = 0,         //�ް���

    KEY_1_DOWN,          //����1����
    KEY_1_UP,            //����1�ɿ�
    KEY_1_LONG,          //����1����

    KEY_2_DOWN,          //����2����
    KEY_2_UP,            //����2�ɿ�
    KEY_2_LONG,          //����2����

    KEY_3_DOWN,          //����3����
    KEY_3_UP,            //����3�ɿ�
    KEY_3_LONG,          //����3����
}KEY_ENUM;

typedef struct
{
    uint8_t (*IsKeyDownFunc)(void);     //�������µ��жϺ�����1��ʾ���£�0��ʾδ����

    uint8_t Count;                      //�˲���������
    uint16_t LongCount;                 //����������
    uint16_t LongTime;                  //����ʱ����ֵ��0��ʾ��֧�ֳ���
    uint8_t State;                      //������ǰ
    uint8_t RepeatSpeed;                //�����ظ�����
    uint8_t RepeatCount;                //��������������
}KEY_T;

void Key_GPIO_Config(void);

static uint8_t IsKey1Down(void);
static uint8_t IsKey2Down(void);
static uint8_t IsKey3Down(void);
static uint8_t IsKey4Down(void);

void KEY_FIFO_Init(void);
void KEY_FIFO_Put(uint8_t Key);
uint8_t KEY_FIFO_Get(void);

static void KEY_Detect(uint8_t i);
void KEY_Scan(void);

void RunPer10ms(void);

#endif

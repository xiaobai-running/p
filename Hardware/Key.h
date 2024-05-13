#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"
#include "stdint.h"

#define KEY_FIFO_SIZE 16  //键值缓冲区大小

typedef struct
{
    uint8_t Buf[KEY_FIFO_SIZE];    //键值缓冲区
    uint8_t Read;                  //缓冲区读指针
    uint8_t Write;                 //缓冲区写指针
}KEY_FIFO_T;

typedef enum
{
    KEY_NONE = 0,         //无按键

    KEY_1_DOWN,          //按键1按下
    KEY_1_UP,            //按键1松开
    KEY_1_LONG,          //按键1长按

    KEY_2_DOWN,          //按键2按下
    KEY_2_UP,            //按键2松开
    KEY_2_LONG,          //按键2长按

    KEY_3_DOWN,          //按键3按下
    KEY_3_UP,            //按键3松开
    KEY_3_LONG,          //按键3长按
}KEY_ENUM;

typedef struct
{
    uint8_t (*IsKeyDownFunc)(void);     //按键按下的判断函数，1表示按下，0表示未按下

    uint8_t Count;                      //滤波器计数器
    uint16_t LongCount;                 //长按计数器
    uint16_t LongTime;                  //长按时间阈值，0表示不支持长按
    uint8_t State;                      //按键当前
    uint8_t RepeatSpeed;                //按键重复周期
    uint8_t RepeatCount;                //连续按键计数器
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

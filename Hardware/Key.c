#include "Key.h"

#define     KEY_NUM          4
#define     KEY_FILTER_TIME  5      

#define     Key_Port    GPIOA
#define     Key1_Pin    GPIO_Pin_2
#define     Key2_Pin    GPIO_Pin_3
#define     Key3_Pin    GPIO_Pin_6
#define     Key4_Pin    GPIO_Pin_7

static KEY_FIFO_T s_tKey;             //Key FIFO structure
static KEY_T      s_tBtn[KEY_NUM];    //Key structure

/// @brief Initialize the GPIO pin of the key
/// @param  
void Key_GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    //Configure the GPIO pin as input
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = Key1_Pin | Key2_Pin | Key3_Pin | Key4_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(Key_Port, &GPIO_InitStructure);
}

/// @brief whether the key is down or not
/// @param  
/// @return 1: key is down, 0: key is up
static uint8_t IsKey1Down(void)
{
    if(GPIO_ReadInputDataBit(Key_Port, Key1_Pin) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
static uint8_t IsKey2Down(void)
{
    if(GPIO_ReadInputDataBit(Key_Port, Key2_Pin) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
static uint8_t IsKey3Down(void)
{
    if(GPIO_ReadInputDataBit(Key_Port, Key3_Pin) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
static uint8_t IsKey4Down(void)
{
    if(GPIO_ReadInputDataBit(Key_Port, Key4_Pin) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/// @brief  Initialize the key FIFO structure
/// @param  
void KEY_FIFO_Init(void)
{
    uint8_t i;

    s_tKey.Read = 0;
    s_tKey.Write = 0;

    for(i = 0; i < KEY_NUM; i++)
    {
        s_tBtn[i].LongTime = 100;
        s_tBtn[i].Count = 5/2;
        s_tBtn[i].State = 0;
        s_tBtn[i].RepeatSpeed = 0;
        s_tBtn[i].RepeatCount = 0;
    }
    s_tBtn[0].IsKeyDownFunc = IsKey1Down;
    s_tBtn[1].IsKeyDownFunc = IsKey2Down;
    s_tBtn[2].IsKeyDownFunc = IsKey3Down;
    s_tBtn[3].IsKeyDownFunc = IsKey4Down;
}

/// @brief  Put a key code into the key FIFO structure
/// @param  _KeyCode: the key code to be put into the FIFO structure
void KEY_FIFO_Put(uint8_t _KeyCode)
{
    s_tKey.Buf[s_tKey.Write] = _KeyCode;

    if(++s_tKey.Write >= KEY_FIFO_SIZE)
    {
        s_tKey.Write = 0;
    }
}

/// @brief  Get a key code from the key FIFO structure
/// @param  
/// @return the key code from the FIFO structure
uint8_t KEY_FIFO_Get(void)
{
    uint8_t ret = 0;

    if(s_tKey.Read == s_tKey.Write)
    {
        return KEY_NONE;
    }
    else
    {
        ret = s_tKey.Buf[s_tKey.Read];

        if(++s_tKey.Read >= KEY_FIFO_SIZE)
        {
            s_tKey.Read = 0;
        }

        return ret;
    }
}

/// @brief  Detect the key status and put the key code into the key FIFO structure
/// @param  i: the index of the key to be detected
static void KEY_Detect(uint8_t i)
{
    KEY_T *pBtn;

    pBtn = &s_tBtn[i];
    if(pBtn->IsKeyDownFunc())
    {
        if(pBtn->Count == KEY_FILTER_TIME)
            pBtn->Count = KEY_FILTER_TIME;
        else if(pBtn->Count < 2 * KEY_FILTER_TIME)
            pBtn->Count++;
        else
        {
            if (pBtn->State == 0)
            {
                pBtn->State = 1;

                KEY_FIFO_Put((uint8_t)(3 * i + 1));
            }

            if(pBtn->LongTime > 0)
            {
                if(pBtn->LongCount < pBtn->LongTime)
                {
                    if(++pBtn->LongCount == pBtn->LongTime)
                    {
                        KEY_FIFO_Put((uint8_t)(3 * i + 3));
                    }
                }
                else
                {
                    if(pBtn->RepeatSpeed > 0)
                    {
                        if(++pBtn->RepeatCount == pBtn->RepeatSpeed)
                        {
                            pBtn->RepeatCount = 0;
                            KEY_FIFO_Put((uint8_t)(3 * i + 1));
                        }
                    }
                }
            }
        }
    }
    else
    {
        if(pBtn->Count > KEY_FILTER_TIME)
        {
            pBtn->Count = KEY_FILTER_TIME;
        }
        else if(pBtn->Count != 0)
        {
            pBtn->Count--;
        }
        else
        {
            if(pBtn->State == 1)
            {
                pBtn->State = 0;

                KEY_FIFO_Put((uint8_t)(3 * i + 2));
            }
        }
        pBtn->LongCount = 0;

        pBtn->RepeatCount = 0;
    }
}

/// @brief Traverse all the keys and detect their status
/// @param  
void KEY_Scan(void)
{
    uint8_t i;

    for(i = 0; i < KEY_NUM; i++)
    {
        KEY_Detect(i);
    }
}

/// @brief scan the key every 10ms
/// @param  
void RunPer10ms(void)
{
    KEY_Scan();
}

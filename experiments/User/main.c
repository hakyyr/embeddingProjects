#include "stm32f10x.h"
#include "OLED.h"
#include "misc.h"

volatile int32_t g_EncoderCount = 0;
volatile uint8_t g_EncoderState = 0;
volatile int8_t g_EncoderDelta = 0;

static void Encoder_Init(void);

int main(void)
{
    int32_t lastCount = 0x7FFFFFFF;

    OLED_Init();
    Encoder_Init();

    while (1)
    {
        if (lastCount != g_EncoderCount)
        {
            lastCount = g_EncoderCount;

            OLED_Clear();
            OLED_ShowString(1, 1, "ENCODER:");
            OLED_ShowSignedNum(2, 1, g_EncoderCount, 5);
            OLED_Update();
        }
    }
}

static void Encoder_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;

    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_Init(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    g_EncoderState =
        (uint8_t)(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) << 1) |
        (uint8_t)GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1);
}

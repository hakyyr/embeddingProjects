#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "OLED.h"
#include "misc.h"

volatile uint32_t g_TimerCount = 0;

static void Timer2_Init(void);

int main(void)
{
    uint32_t lastCount = 0xFFFFFFFF;

    OLED_Init();
    Timer2_Init();

    while (1)
    {
        if (lastCount != g_TimerCount)
        {
            lastCount = g_TimerCount;

            OLED_Clear();
            OLED_ShowString(1, 1, "COUNT:");
            OLED_ShowNum(2, 1, g_TimerCount, 5);
            OLED_Update();
        }
    }
}

static void Timer2_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 10000 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

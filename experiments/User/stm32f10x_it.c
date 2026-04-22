/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

extern volatile int32_t g_EncoderCount;
extern volatile uint8_t g_EncoderState;
extern volatile int8_t g_EncoderDelta;

static void Encoder_DebounceDelay(void)
{
  volatile uint16_t i;

  for (i = 0; i < 300; i++)
  {
  }
}

static void Encoder_Update(void)
{
  uint8_t newState;
  uint8_t transition;

  Encoder_DebounceDelay();

  newState =
    (uint8_t)(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) << 1) |
    (uint8_t)GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1);

  transition = (uint8_t)((g_EncoderState << 2) | newState);

  if (transition == 0x02 || transition == 0x0B || transition == 0x0D || transition == 0x04)
  {
    g_EncoderDelta++;
  }
  else if (transition == 0x01 || transition == 0x07 || transition == 0x0E || transition == 0x08)
  {
    g_EncoderDelta--;
  }

  if (g_EncoderDelta >= 4)
  {
    g_EncoderCount++;
    g_EncoderDelta = 0;
  }
  else if (g_EncoderDelta <= -4)
  {
    g_EncoderCount--;
    g_EncoderDelta = 0;
  }

  g_EncoderState = newState;
}

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}

void EXTI0_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    Encoder_Update();
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

void EXTI1_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    Encoder_Update();
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

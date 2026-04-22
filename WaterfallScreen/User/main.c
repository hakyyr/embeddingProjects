#include "stm32f10x.h"
#include "OLED.h"

void Delay_ms(uint32_t ms);

int main(void)
{
    int16_t offsetX;
    uint8_t i;
    const uint8_t textIndex[] = {2, 3, 4, 5, 6};
    const uint8_t textLength = sizeof(textIndex) / sizeof(textIndex[0]);
    const int16_t textWidth = 16 * textLength;

    OLED_Init();
    OLED_Clear();
    Delay_ms(500);

    while (1)
    {
        for (offsetX = 128; offsetX > -textWidth; offsetX--)
        {
            OLED_Clear();

            for (i = 0; i < textLength; i++)
            {
                OLED_ShowChineseX(2, offsetX + i * 16, textIndex[i]);
            }

            OLED_Update();
            Delay_ms(20);
        }

        OLED_Clear();
        OLED_Update();
        Delay_ms(500);
    }
}

void Delay_ms(uint32_t ms)
{
    uint32_t i;
    uint32_t j;

    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 7200; j++)
        {
        }
    }
}

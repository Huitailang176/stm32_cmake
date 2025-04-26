#include "sys.h"
#include "delay.h"
#include "led.h"



int main(void)
{

    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* ����ʱ��,72M */
    delay_init(72);                             /* ��ʼ����ʱ���� */
    led_init();                                 /* ��ʼ��LED */
    
    while(1)
    {
        LED0(0);                                /* LED0 �� */
        LED1(1);                                /* LED1 �� */
        delay_ms(500);
        LED0(1);                                /* LED0 �� */
        LED1(0);                                /* LED1 �� */
        delay_ms(500);
    }
}


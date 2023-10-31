#include "stm32f10x.h"

uint32_t pwm_value = 0;

void delay_ms(uint32_t ms) 
{
    // �����ӳ�ѭ��ʵ�ֵĺ��뼶�ӳٺ���
    uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 2000; j++) {
            __NOP();
        }
    }
}

int main(void) 
{   
    // ��ʼ�� GPIO �Ͷ�ʱ��
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;

    // ʹ�� GPIO �Ͷ�ʱ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // ���� GPIO
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;                    // ʹ�� PA0 ������Ϊ PWM ���
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // ���ö�ʱ��
    TIM_TimeBaseStruct.TIM_Prescaler     = 72 - 1;              // ����Ԥ��Ƶֵ���õ� 1 MHz �ļ���Ƶ��
    TIM_TimeBaseStruct.TIM_Period        = 1000 - 1;            // ��������Ϊ 1000����Ӧ 1 kHz �� PWM Ƶ��
    TIM_TimeBaseStruct.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);

    // ���ö�ʱ��ͨ�� 1
    TIM_OCInitStruct.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse       = 0;           // ����ռ�ձ�Ϊ 50% ��500/1000��
    TIM_OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

    // ������ʱ��
    TIM_Cmd(TIM2, ENABLE);

    while (1) 
    {
        TIM_SetCompare1(TIM2, pwm_value);
        // ��ʱһ��ʱ�䣬�۲� PWM ����ı仯
        delay_ms(1000);
    }
}

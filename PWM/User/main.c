#include "stm32f10x.h"

uint32_t pwm_value = 0;

void delay_ms(uint32_t ms) 
{
    // 基于延迟循环实现的毫秒级延迟函数
    uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 2000; j++) {
            __NOP();
        }
    }
}

int main(void) 
{   
    // 初始化 GPIO 和定时器
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;

    // 使能 GPIO 和定时器时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 配置 GPIO
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;                    // 使用 PA0 引脚作为 PWM 输出
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 配置定时器
    TIM_TimeBaseStruct.TIM_Prescaler     = 72 - 1;              // 设置预分频值，得到 1 MHz 的计数频率
    TIM_TimeBaseStruct.TIM_Period        = 1000 - 1;            // 设置周期为 1000，对应 1 kHz 的 PWM 频率
    TIM_TimeBaseStruct.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);

    // 配置定时器通道 1
    TIM_OCInitStruct.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse       = 0;           // 设置占空比为 50% （500/1000）
    TIM_OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

    // 启动定时器
    TIM_Cmd(TIM2, ENABLE);

    while (1) 
    {
        TIM_SetCompare1(TIM2, pwm_value);
        // 延时一段时间，观察 PWM 输出的变化
        delay_ms(1000);
    }
}

#include "stm32f10x.h"                  // Device header

void Led_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//初始化LED(1~4)的GPIO
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能APB2外设时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Delay(unsigned long nCount)
{
	while(nCount--  )
	{
	}
}
 
 
int main(void)
{
	int i;
	
	Led_Configuration();
	
	while(1)
	{
		for(i = 0; i < 4000; i++)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_8);
			Delay(i);
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);
			Delay(4000 - i);
		}
		for(i = 0; i < 4000; i++)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);
			Delay(i);
			GPIO_SetBits(GPIOA, GPIO_Pin_8);
            Delay(4000 - i);
        }
	}
}




//#include "stm32f10x.h"

//void delay_ms(uint32_t ms)
//{
//    uint32_t i, j;
//    for (i = 0; i < ms; i++) {
//        for (j = 0; j < 72000; j++);
//    }
//}

//int main(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    TIM_OCInitTypeDef TIM_OCInitStructure;

//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    TIM_TimeBaseStructure.TIM_Period = 1000;
//    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

//    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//    TIM_OCInitStructure.TIM_Pulse = 0;
//    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

//    TIM_Cmd(TIM1, ENABLE);

//    while (1) 
//    {
//        uint16_t i;

//        for (i = 0; i < 1000; i++) 
//        {
//            TIM_SetCompare1(TIM1, i);
//            delay_ms(2);
//        }

//        for (i = 1000; i > 0; i--) 
//        {
//            TIM_SetCompare1(TIM1, i);
//            delay_ms(2);
//        }
//    }
//}

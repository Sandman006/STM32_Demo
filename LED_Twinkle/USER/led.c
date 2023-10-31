/**************************************
 * 文件名  ：led.c
 *          
 * 实验平台：STM32F103C8T6
 * 硬件连接：LED端口PC13,PB12，
 * 备注：修改led端口时要同时修改gpio和pin
         同时加入非精确定时以便调试时使用

*********************************************************/

#include "led.h"

#define LED GPIO_Pin_13

 /***************  配置LED用到的I/O口 *******************/
void LED_GPIO_Config(void)	
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // 使能端口时钟  
    GPIO_InitStructure.GPIO_Pin = LED;	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化端口
    GPIO_SetBits(GPIOC, LED);	 // 关闭所有LED
}
void LED_Toggle(void)
{
	GPIO_WriteBit(GPIOC, LED, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, LED))));//led电平翻转
}
void LED_On()
{
	GPIO_WriteBit(GPIOC, LED,(BitAction)0);
}
void LED_Off()
{
	GPIO_WriteBit(GPIOC, LED,(BitAction)1);
}

void Delayus(u16 i)
{
	unsigned char t = 0;
	for(;i>0;i--)
	{
		for(t=0;t<2;t++)
		{}
	}
}
void Delayms(u16 t)
{
	while(t--)
	{
		Delayus(1000);
	}
}
int LED_Twinkle(int ms)
{
	LED_Off();
	Delayms(ms);
	LED_On();
	Delayms(ms);
	
	return 0;
}

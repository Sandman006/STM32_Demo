#include "stm32f10x.h"                  // Device header
#include "button.h"
#include "led.h"

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

int main(void)
{
	KEY_GPIO_Config();
	LED_GPIO_Config();
	while(1)
	{
		if(Key_Scan(KEY_GPIO_PORT, KEY_GPIO_PIN) == KEY_ON)
			LED_TOGGLE;
	}
}

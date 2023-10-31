#include "stm32f10x.h"                  // Device header
#include "led.h"


void delay_us(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=10;  //????
      while(i--) ;    
   }
}

void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //????
      while(i--) ;    
   }
}

int main(void)
{
	LED_GPIO_Config();
	
	while(1)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		delay_ms(200);

		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		delay_ms(200);
	}
}

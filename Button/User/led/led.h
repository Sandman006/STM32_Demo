#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h" 

#define LED_GPIO_PIN 	GPIO_Pin_13
#define LED_GPIO_PORT 	GPIOC
#define LED_GPIO_CLK 	RCC_APB2Periph_GPIOC

#define LED_ON	1
#define LED_OFF	0

#define LED(a) if(a) \
					GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);\
				else GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);

#define LED_TOGGLE {LED_GPIO_PORT->ODR ^= LED_GPIO_PIN;}

void LED_GPIO_Config(void);

#endif /* __LED_H */

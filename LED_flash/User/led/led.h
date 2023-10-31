#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h" 

#define LED_GPIO_PIN 	GPIO_Pin_13
#define LED_GPIO_PORT GPIOC
#define LED_GPIO_CLK 	RCC_APB2Periph_GPIOC

void LED_GPIO_Config(void);

#endif /*__LED_H*/

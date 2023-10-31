#ifndef __BUTTON_H
#define __BUTTON_H

#include "stm32f10x.h" 

#define KEY_GPIO_PIN 	GPIO_Pin_0
#define KEY_GPIO_PORT 	GPIOA
#define KEY_GPIO_CLK 	RCC_APB2Periph_GPIOA

#define KEY_ON	1
#define KEY_OFF	0

void KEY_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* __BUTTON_H */

#ifndef __BEEP__H
#define __BEEP__H

#include "sys.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//定义GPIOB的位地址变量宏

#define PBout(n) 				BIT_ADDR(GPIOB_ODR_Addr,n)
#define	PBeep 					PBout(5)
#define	BEEP_PORT   		GPIOB
#define BEEP_PIN    		GPIO_Pin_5
#define BEEP_PORT_RCC 	RCC_APB2Periph_GPIOB

void BEEP_Init(void);
void Sound(u16 frq);
void play(void);

#endif

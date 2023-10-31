#ifndef __MAX7219_H
#define __MAX7219_H

#include "stm32f1xx.h"

#define PIN_CLK	GPIO_PIN_13
#define PIN_CS  GPIO_PIN_2
#define PIN_DIN GPIO_PIN_15
														//PB13     ------> SPI2_SCK
														//PB15     ------> SPI2_MOSI

void Write_Byte(uint8_t DATA);
void Write_Max7219(uint8_t addr,uint8_t dat);
void Init_Max7219(void);

#endif

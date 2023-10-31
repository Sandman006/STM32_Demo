#include "MAX7219.h"
#include "spi.h"

 uint8_t code_table[]=
{0x00,0x6C,0x92,0x82,0x44,0x28,0x10,0x00};


//功能：向MAX7219(U3)写入字节
void Write_Byte(uint8_t DATA)
{
	  HAL_GPIO_WritePin(GPIOA,PIN_CS,GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi2,&DATA,1,0xfff);
}

//功能：向MAX7219写入数据
void Write_Max7219(uint8_t addr,uint8_t dat)
{
	Write_Byte(addr);		//写入地址，即数码管编号
	Write_Byte(dat);		//写入数据，即数码管显示数字 
	HAL_GPIO_WritePin(GPIOA,PIN_CS,GPIO_PIN_SET);
	
}

void Init_Max7219(void)
{
	Write_Max7219(0x09, 0x00);				//译码方式：BCD码
	Write_Max7219(0x0a, 0x03);				//亮度 
	Write_Max7219(0x0b, 0x07);        //扫描界限；8个数码管显示
	Write_Max7219(0x0c, 0x01);        //掉电模式：0，普通模式：1
	Write_Max7219(0x0f, 0x00);        //显示测试：1；测试结束，正常显示：0
}

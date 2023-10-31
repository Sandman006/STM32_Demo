#include "MAX7219.h"
#include "spi.h"

 uint8_t code_table[]=
{0x00,0x6C,0x92,0x82,0x44,0x28,0x10,0x00};


//���ܣ���MAX7219(U3)д���ֽ�
void Write_Byte(uint8_t DATA)
{
	  HAL_GPIO_WritePin(GPIOA,PIN_CS,GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi2,&DATA,1,0xfff);
}

//���ܣ���MAX7219д������
void Write_Max7219(uint8_t addr,uint8_t dat)
{
	Write_Byte(addr);		//д���ַ��������ܱ��
	Write_Byte(dat);		//д�����ݣ����������ʾ���� 
	HAL_GPIO_WritePin(GPIOA,PIN_CS,GPIO_PIN_SET);
	
}

void Init_Max7219(void)
{
	Write_Max7219(0x09, 0x00);				//���뷽ʽ��BCD��
	Write_Max7219(0x0a, 0x03);				//���� 
	Write_Max7219(0x0b, 0x07);        //ɨ����ޣ�8���������ʾ
	Write_Max7219(0x0c, 0x01);        //����ģʽ��0����ͨģʽ��1
	Write_Max7219(0x0f, 0x00);        //��ʾ���ԣ�1�����Խ�����������ʾ��0
}

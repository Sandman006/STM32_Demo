#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "QDTFT_demo.h"

int main(void)
{
  SystemInit();	//System init.
  delay_init(72);//Delay init.
 
  while(1)
  {  
		QDTFT_Test_Demo();	//See the test details in QDTFT_Demo.c		
		delay_ms(200);
  }
}

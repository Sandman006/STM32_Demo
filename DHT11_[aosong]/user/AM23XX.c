#include "AM23XX.h"
uint8_t a=0;
uint8_t flag11=0;
uint16_t count =0;
/*
 * 函数名：DHT11_GPIO_Config
 * 描述  ：配置DHT11用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
 void delay(int tt)
 {	   int j;
    for(;tt!=0;tt--)
		for(j=44;j>0;j--);
 }
void DHT11_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOD的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); 

	/*选择要控制的GPIOD引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 

	/*调用库函数，初始化GPIOD*/
  	GPIO_Init(GPIOA, &GPIO_InitStructure);		  

	/* 拉高GPIOD12	*/
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	printf("DHT11 配置完！！");	 
	printf("\n\n");
}

/*
 * 函数名：DHT11_Mode_IPU
 * 描述  ：使DHT11-DATA引脚变为输入模式
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_Mode_IN_FLOATING(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  	/*选择要控制的GPIOD引脚*/	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;

	   /*设置引脚模式为浮空输入模式*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 

	  /*调用库函数，初始化GPIOD*/
	  GPIO_Init(GPIOA, &GPIO_InitStructure);	 
}

/*
 * 函数名：DHT11_Mode_Out_PP
 * 描述  ：使DHT11-DATA引脚变为输出模式
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_Mode_Out_PP(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*选择要控制的GPIOD引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_10MHz;

	/*调用库函数，初始化GPIOD*/
  	GPIO_Init(GPIOA, &GPIO_InitStructure);	 	 
}
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//void SDA_Pin_Output_High(void)
//{
//	GPIOA->DDR |= SDA_Pin;		//输出模式
//	GPIOA->ODR |= SDA_Pin;		//输出'1'	
//	GPIOA->CR1 |= SDA_Pin;		//推挽模式  开漏端口此位无效
//	GPIOA->CR2 |= SDA_Pin;		//高速输出
//}
//
//void SDA_Pin_Output_Low(void)
//{
//	GPIOA->DDR |= SDA_Pin;		 //输出模式
//	GPIOA->ODR &= (~SDA_Pin);		//输出'0'	
//	GPIOA->CR1 |= SDA_Pin;		  //推挽模式  开漏端口此位无效
//	GPIOA->CR2 |= SDA_Pin;		 //高速输出
//}
//
//void SDA_Pin_IN_FLOATING(void)
//{
//	GPIOA->CR2 &= ~(SDA_Pin);			//禁止外部中断
//	GPIOA->DDR &= ~(SDA_Pin);			//输入模式
//	GPIOA->CR1 &= ~(SDA_Pin);			//悬浮输入
//}
//-----------------------------------------------------------------------------------------------
static uint8_t Read_Byte(void)
{	  

   	 uint8_t i, temp=0;

	 for(i=0;i<8;i++)    
	 {
	   /*每bit以50us低电平标置开始，轮询直到从机发出 的50us 低电平 结束*/  
    	while(DHT11_DATA_IN()==Bit_RESET);//{if(++count>5000) break;};
		 
		 /*DHT11 以27~28us的高电平表示“0”，以70us高电平表示“1”，
	 		 通过检测60us后的电平即可区别这两个状态*/

		//delay(5); //延时60us
		SysTickDelay(40);		   	  
	
		  if(DHT11_DATA_IN()==Bit_SET)//60us后仍为高电平表示数据“1”
		   {
		   	/*轮询直到从机发出的剩余的 30us 高电平结束*/
   				 while(DHT11_DATA_IN() ==Bit_SET);//{if(++count>500) break;}
				 // SysTickDelay(1);
				 temp|=(uint8_t)(0x01<<(7-i));  //把第7-i位置1 
			
		   }
		   else	 //60us后为低电平表示数据“0”
		   {//SysTickDelay(1);			   
		   	  temp&=(uint8_t)~(0x01<<(7-i)); //把第7-i位置0
		   }
	 }
	  return temp;
}

uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{  

	DHT11_Mode_Out_PP();
		DHT11_DATA_OUT(HIGH);
		SysTickDelay(500000); 
	/*主机拉低*/
	//DHT11_Mode_Out_PP();
  	DHT11_DATA_OUT(LOW);
   //*延时18ms*/800US
   	SysTickDelay(2000);	//一定要2MS 的起始信号
  //	DHT11_Mode_IN_FLOATING();
   /*总线拉高 主机延时30us*/
   	//DHT11_DATA_OUT(HIGH); 
	DHT11_DATA_OUT(HIGH);
  	SysTickDelay(30);
   	/*主机设为输入 判断从机响应信号*/ 
   //	DHT11_Mode_IN_FLOATING();
	DHT11_Mode_IN_FLOATING();
  //delay(3);
 /*判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行*/   
  //while(DHT11_DATA_IN() ==Bit_SET){a++;if(a>10) break;}
   SysTickDelay(10);
			if(DHT11_DATA_IN()==Bit_RESET)
				{	
					  /*轮询直到从机发出的 80us 高电平 标置信号结束*/
					count =0;
					while(DHT11_DATA_IN()==Bit_RESET);// {if(++count>500) break;}
					count =0;
					while(DHT11_DATA_IN()==Bit_SET);//{if(++count>500) break;}

	  /*轮询直到从机发出的 80us 高电平 标置信号结束*/
	  /*开始接收数据*/   
	 	 			DHT11_Data->humi_int= Read_Byte();	   //0
								
		 			DHT11_Data->humi_deci= Read_Byte();	  //1
				
		 			DHT11_Data->temp_int= Read_Byte();			 //2

		 			DHT11_Data->temp_deci= Read_Byte();			//3
				 		
		 			DHT11_Data->check_sum= Read_Byte();
		 								  
		 delay(1);
		 	/*读取结束，引脚改为输出模式*/
  		 DHT11_Mode_Out_PP();
		   /*主机拉高*/
		 DHT11_DATA_OUT(HIGH);
		 DHT11_Data->check_sum_tep=DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int+ DHT11_Data->temp_deci;
		   /*检查读取的数据是否正确*/
		 if(DHT11_Data->check_sum == DHT11_Data->check_sum_tep)
		  	{
			//	display(DHT11_Data->temp_int,DHT11_Data->humi_int) ;
			//	delay(200000);
			//	display(DHT11_Data->temp_deci,DHT11_Data->humi_deci) ;
			//	delay(200000);
			/* AM23XX 处理程序********/
				DHT11_Data->hh = DHT11_Data->humi_int;
				DHT11_Data->hh <<= 8;
				DHT11_Data->hh |= DHT11_Data->humi_deci;
				if(0>DHT11_Data->hh||DHT11_Data->hh>=1000)DHT11_Data->hh=999;
				

				DHT11_Data->tem = DHT11_Data->temp_int;
				DHT11_Data->tem <<= 8;
				DHT11_Data->tem |= DHT11_Data->temp_deci;
				if(0>DHT11_Data->tem||DHT11_Data->tem>=1000)DHT11_Data->tem=999;


				DHT11_Data->hh_10=DHT11_Data->hh/10;
				DHT11_Data->tem_10 =DHT11_Data->tem/10;


				return SUCCESS;

			}
		  else 
		  	{
		//	printf("和值不相等\n");
			return ERROR;
			}
   }
   else
   	{		
			return ERROR;
		}
   			 	
}

	  


/*************************************END OF FILE******************************/

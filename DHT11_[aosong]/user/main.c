#include "stm32f10x.h"
#include "ili9320.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"
#include "math.h" 
#include "AM23XX.H"
#include <stdio.h>

void SZ_STM32_SysTickInit(uint32_t HzPreSecond);
s32 temperature;
u16 humidity;
void SysTickDelay(__IO uint32_t nTime);
__IO uint32_t TimingDelay;
void SysTickDelay(__IO uint32_t nTime)
{ 
    TimingDelay = nTime;
    while(TimingDelay != 0);		
}
u8 DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PG端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //PG11端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);				 //初始化IO口
 	GPIO_SetBits(GPIOA,GPIO_Pin_5);					//PG11 输出高
	   
	//DHT11_Rst();  //复位DHT11
	printf("\r\n 准备 %dth\r\n",11);
	//return DHT11_Check();//等待DHT11的回应
	return 0;
} 

/* 别名区宏定义 bitband macro ------------------------------------------------*/
/* 使用bitband可以提高设计bit操作的程序的效率，外设GPIO管脚的控制效果尤为明显 */
/* 外设别名区 对32MB外设别名区的访问映射为对1MB 外设bit-band区的访问(实际大小根据芯片有关) */
#define Periph_BASE         0x40000000  // 外设基地址 Peripheral 
#define Periph_BB_BASE      0x42000000  // 外设别名区基地址 Peripheral bitband

/* 注意：传入常量参数时，在编译时编译器会计算出别名区地址，这样能达到提升效率的目的(推荐)
         如果传入变量参数，只能在运行时由STM32自己计算别名区地址，效率会大打折扣(不推荐) */
#define Periph_BB(PeriphAddr, BitNumber)    \
          *(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2))
	 
#define Periph_ResetBit_BB(PeriphAddr, BitNumber)    \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)) = 0)
   
#define Periph_SetBit_BB(PeriphAddr, BitNumber)       \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define Periph_GetBit_BB(PeriphAddr, BitNumber)       \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)))


/* 外设GPIO输入输出别名区定义，n为bit位置范围为0到15    */
/* 我们对GPIOA.15操作，首先要初始化GPIO，然后使用方法： */
/* 对GPIOA.15输出低电平：   PAOutBit(15) = 0;           */
/* 对GPIOA.15输出低电平：   PAOutBit(15) = 1;           */
/* 读取GPIOA.15输入的电平： data = PAInBit(15);         */
#define PAOutBit(n)     Periph_BB((uint32_t)&GPIOA->ODR,n)  //输出 
#define PASetBit(n)     (PAOutBit(n) = 1)                   //输出 高
#define PAResetBit(n)   (PAOutBit(n) = 0)                   //输出 低
#define PAInBit(n)      Periph_BB((uint32_t)&GPIOA->IDR,n)  //输入 
#define PAflowtingBit(n)  Periph_BB((uint32_t)&GPIOA->CRH,n)  //端口浮高

#define PBOutBit(n)     Periph_BB((uint32_t)&GPIOB->ODR,n)  //输出 
#define PBSetBit(n)     (PBOutBit(n) = 1)                   //输出 高
#define PBResetBit(n)   (PBOutBit(n) = 0)                   //输出 低
#define PBInBit(n)      Periph_BB((uint32_t)&GPIOB->IDR,n)  //输入 

#define PCOutBit(n)     Periph_BB((uint32_t)&GPIOC->ODR,n)  //输出 
#define PCSetBit(n)     (PCOutBit(n) = 1)                   //输出 高
#define PCResetBit(n)   (PCOutBit(n) = 0)                   //输出 低
#define PCInBit(n)      Periph_BB((uint32_t)&GPIOC->IDR,n)  //输入 

#define PDOutBit(n)     Periph_BB((uint32_t)&GPIOD->ODR,n)  //输出 
#define PDSetBit(n)     (PDOutBit(n) = 1)                   //输出 高
#define PDResetBit(n)   (PDOutBit(n) = 0)                   //输出 低
#define PDInBit(n)      Periph_BB((uint32_t)&GPIOD->IDR,n)  //输入 

#define PEOutBit(n)     Periph_BB((uint32_t)&GPIOE->ODR,n)  //输出 
#define PESetBit(n)     (PEOutBit(n) = 1)                   //输出 高
#define PEResetBit(n)   (PEOutBit(n) = 0)                   //输出 低
#define PEInBit(n)      Periph_BB((uint32_t)&GPIOE->IDR,n)  //输入

#define PFOutBit(n)     Periph_BB((uint32_t)&GPIOF->ODR,n)  //输出 
#define PFSetBit(n)     (PFOutBit(n) = 1)                   //输出 高
#define PFResetBit(n)   (PFOutBit(n) = 0)                   //输出 低
#define PFInBit(n)      Periph_BB((uint32_t)&GPIOF->IDR,n)  //输入

#define PGOutBit(n)     Periph_BB((uint32_t)&GPIOG->ODR,n)  //输出 
#define PGSetBit(n)     (PGOutBit(n) = 1)                   //输出 高
#define PGResetBit(n)   (PGOutBit(n) = 0)                   //输出 低
#define PGInBit(n)      Periph_BB((uint32_t)&GPIOG->IDR,n)  //输入


/* 内部SRAM别名区 对32MB SRAM别名区的访问映射为对1MB SRAMbit-band区的访问(实际大小根据芯片有关) */
#define RAM_BASE            0x20000000  // 内部SRAM基地址  
#define RAM_BB_BASE         0x22000000  // 内部SRAM别名区基地址

#define SRAM_ResetBit_BB(VarAddr, BitNumber)    \
          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)
   
#define SRAM_SetBit_BB(VarAddr, BitNumber)       \
          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define SRAM_GetBit_BB(VarAddr, BitNumber)       \
          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)))

USART_InitTypeDef USART_InitStructure;

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)


#define DA_PIN_NUM                     11 /* bitband别名区使用宏定义  */
#define DA_PIN                         GPIO_Pin_11
#define DA_GPIO_PORT                   GPIOA
#define DA_GPIO_CLK                    RCC_APB2Periph_GPIOA  
#define DAOBB                          Periph_BB((uint32_t)&DA_GPIO_PORT->ODR, DA_PIN_NUM)
#define PA11_IN()  {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=8<<12;} //浮空输入
#define PA11_OUT() {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=3<<12;} //通用推挽输出  50M
////IO操作函数											   
#define	DHT11_DQ_IN  PAInBit(11)  //数据端口	PA11
#define PA11_0		PAResetBit(11)
#define PA11_1		PASetBit(11)
#define	PA11_INDATA 	PAInBit(11)  //数据端口	PA11

DHT11_Data_TypeDef DHT11_Data;
void SZ_STM32_SysTickInit(uint32_t HzPreSecond)
{
    if (SysTick_Config(SystemCoreClock / HzPreSecond))
    { 
        /* Capture error */ 
        while (1);
    }
}
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    { 
        TimingDelay--;
    }
}

void Delayus(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

void STM32_Shenzhou_COMInit(USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable UART clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  USART_Init(USART1, USART_InitStruct);	/* USART configuration */
  USART_Cmd(USART1, ENABLE);  /* Enable USART */
  //USART_Cmd(USART1, DISABLE);
  
}

/**-------------------------------------------------------
  * @函数名 TimingDelay_Decrement
  * @功能   系统节拍定时器服务函数调用的子函数
  *         将全局变量TimingDelay减一，用于实现延时
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/

/**-------------------------------------------------------
  * @函数名 SysTick_Handler
  * @功能   系统节拍定时器服务请求处理函数
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}

void NVIC_GroupConfig(void)
{
    /* 配置NVIC中断优先级分组:
     - 1比特表示主优先级  主优先级合法取值为 0 或 1 
     - 3比特表示次优先级  次优先级合法取值为 0..7
     - 数值越低优先级越高，取值超过合法范围时取低bit位 
    */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /*==================================================================================
      NVIC_PriorityGroup   |  主优先级范围  |  次优先级范围  |   描述
      ==================================================================================
     NVIC_PriorityGroup_0  |      0         |      0-15      |   0 比特表示主优先级
                           |                |                |   4 比特表示次优先级 
     ----------------------------------------------------------------------------------
     NVIC_PriorityGroup_1  |      0-1       |      0-7       |   1 比特表示主优先级
                           |                |                |   3 比特表示次优先级 
     ----------------------------------------------------------------------------------
     NVIC_PriorityGroup_2  |      0-3       |      0-3       |   2 比特表示主优先级
                           |                |                |   2 比特表示次优先级 
     ----------------------------------------------------------------------------------
     NVIC_PriorityGroup_3  |      0-7       |      0-1       |   3 比特表示主优先级
                           |                |                |   1 比特表示次优先级 
     ----------------------------------------------------------------------------------
     NVIC_PriorityGroup_4  |      0-15      |      0         |   4 比特表示主优先级
                           |                |                |   0 比特表示次优先级   
    ==================================================================================*/
}
/**-------------------------------------------------------
  * @函数名 SZ_STM32_SysTickInit
  * @功能   初始化系统定时器SysTick
  *         用户可以根据需要修改
  * @参数   每秒中断次数
  * @返回值 无
***------------------------------------------------------*/

//USART_InitTypeDef USART_InitStructure;
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

//static void Delay_ARMJISHU(__IO uint32_t nCount)
//{
// // for (; nCount != 0; nCount--);
//}

void Read_Sensor()
{	// 读取传感器数据
	if( Read_DHT11(&DHT11_Data)==SUCCESS)										 //“\”表示转向一下行
	{
		printf("\r\n读取DHT11成功!\r\n\r\n湿度为十六进制：%02x.%02x ％RH ，温度为十六进制：%02x.%02x ℃ \r\n",\
		DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);

		printf("\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n",\
		DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		display(DHT11_Data.tem_10,DHT11_Data.hh_10) ;
	}	  
}

int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured, 
		 this is done through SystemInit() function which is called from startup
		 file (startup_stm32f10x_xx.s) before to branch to application main.
		 To reconfigure the default setting of SystemInit() function, refer to
		 system_stm32f10x.c file
	 */     
								
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	STM32_Shenzhou_COMInit(&USART_InitStructure);
	SZ_STM32_SysTickInit(1000000);
	/* Output a message on Hyperterminal using printf function */
	ili9320_Initializtion();
	printf("\r\n 准备初始化 %dth\r\n",11);
	/*TFT-LCD彩屏显示数字1*/  
	jiemian();
	DHT11_GPIO_Config(); 
		
		
		
	while(1)
	{	   
		Read_Sensor();		  // 读取传感器数据
	} 			   
}

PUTCHAR_PROTOTYPE
{
  USART_SendData(USART1, (uint8_t) ch);

  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

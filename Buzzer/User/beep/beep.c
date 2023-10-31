#include "beep.h"
#include "systick.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_mode;
	RCC_APB2PeriphClockCmd(BEEP_PORT_RCC, ENABLE);         //使能GPIOB时钟
	GPIO_mode.GPIO_Pin = BEEP_PIN;
	GPIO_mode.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_mode.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(BEEP_PORT, &GPIO_mode);      //设置GPIOB5为推挽输出，50MHz速度
}

void Sound(u16 frq)
{
	u32 n;
	if(frq != 1000) //如果频率不为1000则按频率输出，否则只延时
	{
		 n = 500000/((u32)frq);
		 PBeep = 0;
		 delay_us(n);
		 PBeep = 1;
		 delay_us(n);
	}else
		 delay_us(1000);
}

void play(void)
{
//             低7  1   2   3   4   5   6   7  高1 高2 高3 高4 高5 不发音
	uc16 tone[] = {247,262,294,330,349,392,440,494,523,587,659,698,784,1000};//音频数据表
	//红尘情歌
	u8 music[] = {       
		5,5,6,8,7,6,5,6,13,13,//音调
		5,5,6,8,7,6,5,3,13,13,
		2,2,3,5,3,5,6,3,2,1,
		6,6,5,6,5,3,6,5,13,13,
		5,5,6,8,7,6,5,6,13,13,
		5,5,6,8,7,6,5,3,13,13,
		2,2,3,5,3,5,6,3,2,1,
		6,6,5,6,5,3,6,1,   
		13,8,9,10,10,9,8,10,9,8,6,
		13,6,8,9,9,8,6,9,8,6,5,
		13,2,3,5,5,3,5,5,6,8,7,6,
		6,10,9,9,8,6,5,6,8
	};     

	u8 time[] = {       
		2,4,2,2,2,2,2,8,4, 4, //时间
		2,4,2,2,2,2,2,8,4, 4,
		2,4,2,4,2,2,4,2,2,8,
		2,4,2,2,2,2,2,8,4 ,4,
		2,4,2,2,2,2,2,8,4, 4,
		2,4,2,2,2,2,2,8,4, 4,
		2,4,2,4,2,2,4,2,2,8,
		2,4,2,2,2,2,2,8,4, 
		2,2,2,4,2,2,2,2,2,8,
		4,2,2,2,4,2,2,2,2,2,8,
		4,2,2,2,4,2,2,5,2,6,2,4,
		2,2,2,4,2,4,2,2,12
	};     
	u32 yanshi;
	u16 i,e;
	yanshi = 10;

	for(i=0;i<sizeof(music)/sizeof(music[0]);i++){
		 for(e=0;e<((u16)time[i])*tone[music[i]]/yanshi;e++){
							Sound((u32)tone[music[i]]);
		 }      
	}
}

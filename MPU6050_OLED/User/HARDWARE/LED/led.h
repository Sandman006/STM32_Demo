#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0 PCout(13)	

//��ʼ��
void LED_Init(void);
void LED_blink(void);
	 				    
#endif

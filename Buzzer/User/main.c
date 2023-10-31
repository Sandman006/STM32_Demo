#include "beep.h"
#include "SysTick.h"

int main()
{
	SysTick_Init(72);
	BEEP_Init();
	while(1)
	{
		 play();
	}
}

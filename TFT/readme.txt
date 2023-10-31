#define LCD_CTRL   	  	GPIOB			//定义TFT数据端口
#define LCD_LED        	GPIO_Pin_9  	//PB9 连接至TFT - LED
#define LCD_RS         	GPIO_Pin_10		//PB10连接至TFT - RS
#define LCD_CS        	GPIO_Pin_11 	//PB11连接至TFT - CS
#define LCD_RST     	GPIO_Pin_12		//PB12连接至TFT - RST
#define LCD_SCL        	GPIO_Pin_13		//PB13连接至TFT - CLK
#define LCD_SDA        	GPIO_Pin_15		//PB15连接至TFT - SDI


VCC: 可以接5V也可以接3.3V
LED: 可以接5V也可以接3.3V或者使用任意空闲IO控制(高电平使能)
GND：接电源地
说明:	如需要尽可能少占用IO，可以将LCD_CS接地，LCD_LED接3.3V，LCD_RST接至单片机复位端，将可以释放3个可用IO
		接口定义在Lcd_Driver.h内定义，如需变更IO接法，请根据您的实际接线修改相应IO初始化LCD_GPIO_Init()

/**@file   bsp_io.c
* @brief   IO口驱动
* @version 1.00.0.0
**************************************************************************************************/

/**************************************************************************************************
*                                      INCLUDE FILES
**************************************************************************************************/

#include "bsp_io.h"

/**************************************************************************************************
*                                      MACROS DEFINE
**************************************************************************************************/


/**************************************************************************************************
*                                      DATA TYPES
**************************************************************************************************/


/**************************************************************************************************
*                                      VARIABLES
**************************************************************************************************/


/**************************************************************************************************
*                                      FUNCTION PROTOTYPES
**************************************************************************************************/

/**
* @brief  LED小灯
* @attention 
*/
void BspLedInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    GPIO_StructInit(&GPIO_InitStructure);  //结构体初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO的时钟
    //小灯D1~D4
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_12;  //引脚号
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO口驱动电路响应速度
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;  //模式
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化
    //关闭
    LEDA_OFF;
}
/* 输出IO口 */
void BspOutputGPIOInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    GPIO_StructInit(&GPIO_InitStructure);

}
/* 输入IO口 */
void BspInputGPIOInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    GPIO_StructInit(&GPIO_InitStructure);

}
    
/* IO口控制初始化 */
void BspIOInit(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);  //使能GPIO时钟
    BspLedInit();  //LED小灯IO口初始化
//    BspOutputGPIOInit();
//    BspInputGPIOInit();
}

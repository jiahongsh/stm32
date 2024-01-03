#include "stm32f10x.h"                  // Device header
//光敏电阻相当于按键，属于输入
void LightSensor_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启时钟
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输出，保证默认高电平
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;                                           
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}


uint8_t LightSensor_Get(void){
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}

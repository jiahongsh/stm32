#include "stm32f10x.h"                  // Device header


GPIO_InitTypeDef GPIO_InitStructure;
int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//开启使能->定义一个名字->选择推挽模式（高低电频）->选择p13口->速度
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//通用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);//将pin13口设为高电频
	//GPIO_ResetBits(GPIOC,GPIO_Pin_13);//将pin13口设为低电频
	while(1){
		
	}
	
}

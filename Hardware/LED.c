#include "stm32f10x.h"                  // Device header


void LED_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;//配置初始化结构体数据
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;//输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_2;//引脚位置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//让灯默认熄灭
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
}

//点灯
void LED_ON(uint16_t GPIO_Pin){
	GPIO_ResetBits(GPIOA,GPIO_Pin);
}

//关灯
void LED_OFF(uint16_t GPIO_Pin){
	GPIO_SetBits(GPIOA,GPIO_Pin);
}

void LED_Turn(uint16_t GPIO_Pin){
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin)==0){//如果输出寄存器为0，为低电平，灯被点亮
		GPIO_SetBits(GPIOA,GPIO_Pin);
	}else{
		GPIO_ResetBits(GPIOA,GPIO_Pin);
	}
	
}


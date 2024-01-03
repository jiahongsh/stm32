#include "stm32f10x.h"                  // Device header


void Buzzer_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;//配置初始化结构体数据
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;//输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;//引脚位置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//让灯默认熄灭
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

//蜂鸣器开
void Buzzer_ON(uint16_t GPIO_Pin){
	GPIO_ResetBits(GPIOB,GPIO_Pin);
}

//蜂鸣器关
void Buzzer_OFF(uint16_t GPIO_Pin){
	GPIO_SetBits(GPIOB,GPIO_Pin);
}

void Buzzer_Turn(uint16_t GPIO_Pin){
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin)==0){//如果输出寄存器为0，为低电平，蜂鸣器被点亮
		GPIO_SetBits(GPIOB,GPIO_Pin);
	}else{
		GPIO_ResetBits(GPIOB,GPIO_Pin);
	}
	
}


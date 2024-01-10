#include "stm32f10x.h"                  // Device header

void PWM_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;//配置初始化结构体数据
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_AF_PP;//复用推挽输出模式，将输出交给外设
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//引脚位置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启通用定时器的时钟
	
	TIM_InternalClockConfig(TIM2);//调用内部时钟
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分频，相当于规定采样频率的大小
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式，这里选择向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period=100-1;//ARR自动重装器的值   ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler=720-1;//PSC预分频器的值   PSC 10000*7200=72M=72000000 对72M进行7200分频，得到10k的计数频率，即记10k个数为1s
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复计数器的值，高级计数器中使用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);//初始化时基单元
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//手动清除初始化时基单元时的标志位
	                  //更新中断
	//TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能中断函数
	
	//输出比较定时器
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//输出比较模式
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;//输出比较极性
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//输出比较状态，输出使能
	TIM_OCInitStruct.TIM_Pulse=0;//CCR的值
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);
	
	
	TIM_Cmd(TIM2,ENABLE);//启动定时器
	
	
	
}


void PWM_SetCompare1(uint16_t Compare){
	
   TIM_SetCompare1(TIM2,Compare);
	
}
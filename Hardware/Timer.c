#include "stm32f10x.h"                  // Device header

extern uint16_t Num;//声明我有这个变量

void Timer_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启通用定时器的时钟
	
	TIM_InternalClockConfig(TIM2);//调用内部时钟
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分频，相当于规定采样频率的大小
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式，这里选择向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period=10000-1;//ARR自动重装器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;//PSC预分频器的值  10000*7200=72M=72000000 对72M进行7200分频，得到10k的计数频率，即记10k个数为1s
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复计数器的值，高级计数器中使用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);//初始化时基单元
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//手动清除初始化时基单元时的标志位
	                  //更新中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能中断函数
	
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;//中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;//响应优先级
	NVIC_Init(&NVIC_InitStructure);//初始化NVIC
	
	TIM_Cmd(TIM2,ENABLE);//启动定时器
	
}


void TIM2_IRQHandler(void){

    if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)==SET){//检查中断标志位
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);//清除标志位
	}
	
}	

#include "stm32f10x.h"                  // Device header



void Encoderin_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//开启通用定时器的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;//配置初始化结构体数据
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入模式，将输出交给外设
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 |GPIO_Pin_7;//引脚位置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分频，相当于规定采样频率的大小
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式，这里选择向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period=65536-1;//ARR自动重装器的值   ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//PSC预分频器的值   PSC 10000*7200=72M=72000000 对72M进行7200分频，得到10k的计数频率，即记10k个数为1s
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复计数器的值，高级计数器中使用
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);//初始化时基单元
	//TIM_ClearFlag(TIM3,TIM_FLAG_Update);//手动清除初始化时基单元时的标志位
	
	//输入捕获单元
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);//对结构体进行默认初始化
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;//选择通道
	TIM_ICInitStructure.TIM_ICFilter=0xF;//滤波器
	//TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//选择触发模式为上升沿
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;//选择通道
	TIM_ICInitStructure.TIM_ICFilter=0xF;//滤波器
	//TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//选择触发模式为上升沿
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	//配置编码器接口
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//定时器接口编码器配置
	
	
	TIM_Cmd(TIM3,ENABLE);//开启定时器
}


int16_t Encoderin_Get(void){
	int16_t Tmp;
	Tmp=TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return Tmp;
	
}


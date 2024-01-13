#include "stm32f10x.h"                  // Device header

uint16_t Size;
void MyDMA_Init(uint32_t AdderA,uint32_t AdderB,uint16_t BufferSize){
	Size=BufferSize;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr= AdderA;//起始地址
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;//数据宽度
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable;//是否自增
	DMA_InitStructure.DMA_MemoryBaseAddr=AdderB;
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;//传输方向
	DMA_InitStructure.DMA_BufferSize=BufferSize;//传输计数器
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;//是否使用自动重装,选择不循环
	DMA_InitStructure.DMA_M2M=DMA_M2M_Enable;//选择硬件触发还是软件触发，软件触发
	DMA_InitStructure.DMA_Priority=DMA_Priority_VeryHigh;//优先级
	        //软件触发，通道任意
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1,DISABLE);
}


void MyDMA_Tansfer(){
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,Size);//输入传输计数器的值
	DMA_Cmd(DMA1_Channel1,ENABLE);
	//等待转运完成
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);//判断完成标志位
	DMA_ClearFlag(DMA1_FLAG_TC1);//清除标志位
}

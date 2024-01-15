#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include<stdio.h>

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;
void Serial_Init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;//配置初始化结构体数据
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_AF_PP;//输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//引脚位置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;//输入模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//引脚位置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//初始化UUSART1
	 USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;//波特率
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//是否使用流控制
	USART_InitStructure.USART_Mode=USART_Mode_Tx |USART_Mode_Rx;//选择发送模式
	USART_InitStructure.USART_Parity=USART_Parity_No;//校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); //开启中断
	
	//开启NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel =USART1_IRQn;//中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);//开启使能
}


void Serial_SendByte(uint8_t Byte){
	
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE==RESET));//判断发送数据寄存器空标志位
	
}

void Serial_SendArray(uint8_t*Array,uint32_t Length){//发送一个数组
	uint16_t i;
	for(i=0;i<Length;i++){
		
	Serial_SendByte(Array[i]);
		Delay_ms(50);
	}
	
	
}


void Serial_SendString(char* String){
	uint8_t i;
     for(i=0;String[i]!='\0';i++){
		
		Serial_SendByte(String[i]);
		Delay_ms(50);	
		
	}
}

uint32_t Serial_Pow(uint32_t x,uint32_t y){//次方函数
	uint32_t Result=1;
	while(y--){
		Result*=x;
		
	}
	return Result;
	
}

void Serial_SendNumber(uint32_t Number,uint16_t Length){//发送数字
	
uint32_t i;
	for(i=0;i<=Length;i++){
		Serial_SendByte(Number/Serial_Pow(10,Length-1-i)%10+'0');
		Delay_ms(20);
		
		
	}
	
	
}



int fputc(int ch,FILE* f){
	
	Serial_SendByte(ch);
	Delay_ms(20);
	return ch;
}


//void Serial_Print(char*format,...){
//	
//	char String[100];
//	va_list arg;//可变参数列表
//	va_start(arg,format);
//	vsprintf(String,format,arg);
//	va_end(arg);
//	Serial_SendByte(String);
//	
//	
//}
uint8_t Serial_GetFlag(void){
	if(Serial_RxFlag==1){
	  Serial_RxFlag=0;
	  return 1;	
   }    
	  return 0; 
}

uint8_t Serial_GetData(void){
	return Serial_RxData;
 }
void USART1_IRQHandler(void){                        
	Serial_RxData=USART_ReceiveData(USART1);
	Serial_RxFlag=1;
	  if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET){
		  
		  USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	  }
	
	
}

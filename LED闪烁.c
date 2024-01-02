#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//	开启时钟
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//选择推挽输出模式
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;//选择引脚
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;//选择输出速度
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	while(1){
		
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	Delay_ms(500);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);	
	Delay_ms(500);
	}
}

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//	开启时钟
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//选择推挽输出模式
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;//选择引脚
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;//选择输出速度
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	while(1){
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	Delay_ms(500);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	Delay_ms(500);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	Delay_ms(200);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	Delay_ms(200);
//	GPIO_Write(GPIOA,~0x0001);
//	Delay_ms(100);
//	GPIO_Write(GPIOA,~0x0002);	
//	Delay_ms(100);
//	GPIO_Write(GPIOA,~0x0004);
//	Delay_ms(100);
//	GPIO_Write(GPIOA,~0x0008);	
//	Delay_ms(100);
//	GPIO_Write(GPIOA,~0x0010);
//	Delay_ms(100);
//	GPIO_Write(GPIOA,~0x0020);	
//	Delay_ms(100);
//	GPIO_Write(GPIOA,~0x0040);
//	Delay_ms(100);
//	GPIO_Write(GPIOA,~0x0080);	
//	Delay_ms(100);
	}
}

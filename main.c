#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//	开启时钟
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//选择推挽输出模式
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_All;//选择引脚
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;//选择输出速度
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	while(1){
	   uint16_t i;
	 i=0x0001;
	 //利用循环的方式进行调配
	for(i=0x0001;i<0x0080;i<<=1){
		
	GPIO_Write(GPIOA,~i);
	Delay_ms(200);	
	}		
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

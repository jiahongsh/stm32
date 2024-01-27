#include "stm32f10x.h"                  // Device header


void MySPI_W_SS(uint8_t BitValue){ //从机选择
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
	
}

//void MySPI_W_SCK(uint8_t BitValue){ //时钟
//	
//	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)BitValue);
//	
//}

//void MySPI_W_MOSI(uint8_t BitValue){ //从机输入，主机输出
//	
//	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)BitValue);
//	
//}

//uint8_t MySPI_R_MISO(void){ //从机输出，主机输入，返回值给主机
//	
//	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
//}

void MySPI_Init(void){
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;//配置初始化结构体数据
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;//引脚位置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5 |GPIO_Pin_7;//引脚位置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;//上拉输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;//引脚位置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;//高位先行
    SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2; //分频系数
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;
    SPI_InitStructure.SPI_CRCPolynomial=7;
	SPI_Init(SPI1,&SPI_InitStructure);
	
	SPI_Cmd(SPI1,ENABLE);
	
	MySPI_W_SS(1);//默认不选择从机
}


void MySPI_Start(){
	
	MySPI_W_SS(0);
	
}


void MySPI_End(){
	
	MySPI_W_SS(1);
	
}

uint8_t MySPI_SwapByte(uint8_t ByteSend){ //交换一个字节，模式0
	  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)!=SET);
	
	  SPI_I2S_SendData(SPI1,ByteSend);
	 
	   while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)!=SET);
	
	return SPI_I2S_ReceiveData(SPI1);
	
	
}

//uint8_t MySPI_SwapByte(uint8_t ByteSend){ //交换一个字节,契合移位模型
//	  uint8_t i=0;
//	for(i=0;i<8;i++)
//	{ MySPI_W_MOSI(ByteSend & 0x80);//取出最高位
//		ByteSend<<=1;
//	  MySPI_W_SCK(1); //此阶段从机自动把MOSI上的数据读走
//		 if( MySPI_R_MISO()==1)
//	     {
//		    ByteSend |=0x01;
//	     }
//	  MySPI_W_SCK(0);	
//	}
//	 
//	
//	return ByteSend;
//	
//	
//}

//uint8_t MySPI_SwapByte(uint8_t ByteSend){ //交换一个字节，模式1
//	 uint8_t i, ByteReceive=0x00;
//	
//	for(i=0;i<8;i++)
//	{   MySPI_W_SCK(1); //此阶段从机自动把MOSI上的数据读走
//		MySPI_W_MOSI(ByteSend & (0x80>>i));//取出最高位
//	    MySPI_W_SCK(0);
//		 if( MySPI_R_MISO()==1)
//	     {
//		 ByteReceive |=(0x80>>i);
//	     }
//	 	
//	}
//	 
//	
//	return ByteReceive;
//	
//	
//}


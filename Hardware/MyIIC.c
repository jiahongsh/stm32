//#include "stm32f10x.h"                  // Device header
//#include "Delay.h"
//void MyI2C_W_SLC(uint8_t BitValue){
//	 GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);//对SCL写
//	 Delay_us(10);
//	
//}


//void MyI2C_W_SDA(uint8_t BitValue){
//	 GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);//对SDA写
//	 Delay_us(10);
//	
//}


//uint8_t MyI2C_R_SDA(){
//	
//	uint8_t BitValue;
//	BitValue=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
//	 Delay_us(10);
//	return BitValue;
//}

// 
//void MyI2C_Init(void){
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启时钟
//	
//	GPIO_InitTypeDef GPIO_InitStructure;//配置初始化结构体数据
//	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_OD;//输出模式,开漏输出，可以输入
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10 | GPIO_Pin_11;//引脚位置
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//     GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);//将输出模式置为高电平，释放IIC总线
//}


////时序基本单元
//void MyI2C_Start(void){ //起始条件
//	MyI2C_W_SDA(1);//
//	MyI2C_W_SLC(1);
//	MyI2C_W_SDA(0);//
//	MyI2C_W_SLC(0);	
//}

// 
//void MyI2C_Stop(void){//结束条件
//	MyI2C_W_SDA(0);
//	MyI2C_W_SLC(1);
//	MyI2C_W_SDA(1);
//}


//void MyI2C_SendByte(uint8_t Byte){//发送一个字节
//	 uint8_t i=0;
//	for(i=0;i<8;i++){
//	 MyI2C_W_SDA(Byte&(0x80>>i));
//	 MyI2C_W_SLC(1);
//	 MyI2C_W_SLC(0);
//		
//		
//	}
//		
//}

//uint8_t MyI2C_ReceiveByte(void){//主机接收一个字节
//	  uint8_t Byte=0x00;
//	  uint8_t i=0;
//	  MyI2C_W_SDA(1);//我们操作的一直是主机
//    
//	for(i=0;i<8;i++)
//	{
//		MyI2C_W_SLC(1);
//       if(MyI2C_R_SDA()==1)
//		{
//		  Byte |=(0x80>>i);//将Byte置1  
//	    }
//		MyI2C_W_SLC(0);
//	}
//	return Byte;
//}

//void MyI2C_SendByAck(uint8_t AckByte){//发送应答位
//	 
//	
//	 MyI2C_W_SDA(AckByte);
//	 MyI2C_W_SLC(1);
//	 MyI2C_W_SLC(0);
//		
//			
//}
// 
//uint8_t MyI2C_ReceiveAck(void){//主机接收应答位
//	  uint8_t AckByte;
//	  
//	  MyI2C_W_SDA(1);//我们操作的一直是主机
//      MyI2C_W_SLC(1);
//	
//      AckByte= MyI2C_R_SDA();
//      MyI2C_W_SLC(0);
//	
//	return AckByte;
//}
#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MyI2C_W_SCL(uint8_t BitValue){
	 GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);//对SCL写
	 Delay_us(10);
	
}

void MyI2C_W_SDA(uint8_t BitValue){
	 GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);//对SDA写
	 Delay_us(10);
	
}

uint8_t MyI2C_R_SDA(){
	
	uint8_t BitValue;
	BitValue=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	 Delay_us(10);
	return BitValue;
}

void MyI2C_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;//配置初始化结构体数据
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_OD;//输出模式,开漏输出，可以输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10 | GPIO_Pin_11;//引脚位置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//传输速度
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
     GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);//将输出模式置为高电平，释放IIC总线
}

//时序基本单元
void MyI2C_Start(void){ //起始条件
	MyI2C_W_SDA(1);//
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);//
	MyI2C_W_SCL(0);	
}

void MyI2C_Stop(void){//结束条件
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}


void MyI2C_SendByte(uint8_t Byte){//发送一个字节
	 uint8_t i=0;
	for(i=0;i<8;i++){
	 MyI2C_W_SDA(Byte&(0x80>>i));
	 MyI2C_W_SCL(1);
	 MyI2C_W_SCL(0);
		
		
	}
		
}

uint8_t MyI2C_ReceiveByte(void){//主机接收一个字节
	  uint8_t Byte=0x00;
	  uint8_t i=0;
	  MyI2C_W_SDA(1);//我们操作的一直是主机
    
	for(i=0;i<8;i++)
	{
		MyI2C_W_SCL(1);
       if(MyI2C_R_SDA()==1)
		{
		  Byte |=(0x80>>i);//将Byte置1  
	    }
		MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendByAck(uint8_t AckByte){//发送应答位
	 
	
	 MyI2C_W_SDA(AckByte);
	 MyI2C_W_SCL(1);
	 MyI2C_W_SCL(0);
		
			
}
 
uint8_t MyI2C_ReceiveAck(void){//主机接收应答位
	  uint8_t AckByte;
	  
	  MyI2C_W_SDA(1);//我们操作的一直是主机
      MyI2C_W_SCL(1);
	
      AckByte= MyI2C_R_SDA();
      MyI2C_W_SCL(0);
	
	return AckByte;
}
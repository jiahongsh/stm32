#include "stm32f10x.h"                  // Device header
#include "MyIIC.h"
#include "Delay.h"
#include "OLED_Data.h"



void OLED_WriteCommand(uint8_t Command)
{   
	MyI2C_Start();
	MyI2C_SendByte(0x78); //寻址
	MyI2C_ReceiveAck();
	MyI2C_SendByte(0x00); //Control Byte,进入非连续模式 ,写命令
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Command); 
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

void OLED_WriteData(uint8_t Data)
{   
	MyI2C_Start();
	MyI2C_SendByte(0x78); //寻址
	MyI2C_ReceiveAck();
	MyI2C_SendByte(0x40); //Control Byte,进入非连续模式 ,写数据
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data); 
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}


	

void OLED_SetPostion(uint8_t X,uint8_t Page)//显示函数
{
	OLED_WriteCommand(0xB0 | Page);					//设置页位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置低4位
}
void OLED_Init()
{ 
	MyI2C_Init();
	Delay_ms(100);
	
	OLED_WriteCommand(0xAE);//显示关闭
	
	OLED_WriteCommand(0xD5);
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);
	
	OLED_WriteCommand(0xA1);
	
	OLED_WriteCommand(0xC8);
	
	OLED_WriteCommand(0xDA);
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);
	OLED_WriteCommand(0xCF);
	
	OLED_WriteCommand(0xD9);
	OLED_WriteCommand(0xF1);
	
	OLED_WriteCommand(0x30);
	
	OLED_WriteCommand(0xA4);
	
	OLED_WriteCommand(0xA6);
	
	OLED_WriteCommand(0x8D);
	OLED_WriteCommand(0x14);
	
	OLED_WriteCommand(0xAF);
	
	Delay_ms(100);
	
}

void OLED_Clear(){
	uint8_t j=0;
	for(j=0;j<8;j++){
		uint8_t i=0;
		OLED_SetPostion(0,j);
		for(i=0;i<128;i++){
		    OLED_WriteData(0x00);	
		}
		
	}
	
}

 void OLED_ShowChar(uint8_t X,uint8_t Page,char Char,uint8_t FontSize){ //字符显示函数
	 if(FontSize==8)
	 {
		 
	  OLED_SetPostion(X,Page);
	  uint8_t i=0;
	  for(i=0;i<8;i++)
	  {
        OLED_WriteData(OLED_F8x16[Char-' '][i]);
	  }
	   OLED_SetPostion(X,Page+1);
	   for(i=0;i<8;i++)
	  {
        OLED_WriteData(OLED_F8x16[Char-' '][i+8]);
	  } 
	
     }
	 else
	 {
	   OLED_SetPostion(X,Page);
	   uint8_t i=0;
	   for(i=0;i<8;i++)
	   {
        OLED_WriteData(OLED_F6x8[Char-' '][i]);
	   } 
		 
	 }
}
 
void OLED_ShowString(uint8_t X,uint8_t Page,char* String,uint8_t FontSize)
{
    for(uint8_t i=0;String[i]!='\0';i++)
	{
		
		 OLED_ShowChar(X+i*FontSize,Page,String[i],FontSize);
		
	}
	
	
}

void OLED_ShowImage(uint8_t X, uint8_t Page, uint8_t Width, uint8_t Height,const uint8_t *Image){
	  OLED_SetPostion(X,Page);
	for(uint8_t i=0;i<Height;i++){
		OLED_SetPostion(X,Page+i);
		for(uint8_t j=0;j<Width;j++){
			OLED_WriteData(Image[Width*i+j]);
		}
		
	}
	
}



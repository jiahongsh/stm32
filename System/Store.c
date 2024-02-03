#include "stm32f10x.h"                  // Device header
#include "MyFLASH.h"


#define STORE_START_ADDRESS 0X800FC00    
#define STORE_COUNT 512
uint16_t Store_Data[STORE_COUNT];
void Store_Init(){
	//闪存初始化
	if(MyFLASH_ReadHalfWord(STORE_START_ADDRESS)!=0xA5A5){
		  MyFLASH_RrasePage(STORE_START_ADDRESS);
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS,0xA5A5);
	}
	 uint16_t i;
	for(i=1;i<STORE_COUNT;i++){
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS+i*2,0x0000);
	}
	
    for(i=0;i<STORE_COUNT;i++){
		Store_Data[i]=MyFLASH_ReadHalfWord(STORE_START_ADDRESS+i*2);
		
	}
}

void Store_Save(){
	   MyFLASH_RrasePage(STORE_START_ADDRESS);
	   uint16_t i;
	
	
    for(i=0;i<STORE_COUNT;i++){
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS+i*2,Store_Data[i]);
		
	}
}

void Store_Clear(){
	 
     uint16_t i;
    for(i=0;i<STORE_COUNT;i++){
		Store_Data[i]=0x0000;
		
	}
	Store_Save();
}

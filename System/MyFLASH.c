#include "stm32f10x.h"                  // Device header

uint32_t MyFLASH_ReadWord(uint32_t Address){
	return *((__IO uint32_t*)(Address)); 
	
}

uint16_t MyFLASH_ReadHalfWord(uint32_t Address){
	return *((__IO uint16_t*)(Address)); 
	
}

uint8_t MyFLASH_ReadByte(uint32_t Address){
	return *((__IO uint8_t*)(Address)); 
	
}

void MyFLASH_RraseAllPages(void){//数据全擦除
	FLASH_Unlock();//写保护解锁
	FLASH_EraseAllPages();
	FLASH_Lock();//上锁
}

void MyFLASH_RrasePage(uint32_t PageAddress){//页擦除
	FLASH_Unlock();//写保护解锁
	FLASH_ErasePage(PageAddress);
	FLASH_Lock();//上锁
}


void MyFLASH_ProgramWord(uint32_t Address,uint32_t Data){
	 FLASH_Unlock();//写保护解锁
	 FLASH_ProgramWord(Address,Data);
	 FLASH_Lock();//上锁
}

void MyFLASH_ProgramHalfWord(uint32_t Address,uint32_t Data){
	 FLASH_Unlock();//写保护解锁
	 FLASH_ProgramHalfWord(Address,Data);
	 FLASH_Lock();//上锁
}


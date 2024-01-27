#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"
void W25Q64_Init(void){
	
	MySPI_Init();
}

void W25Q64_ReadID(uint8_t *MID,uint16_t *DID){
	 MySPI_Start();
	 MySPI_SwapByte(W25Q64_JEDEC_ID); //读ID号的指令
	*MID=MySPI_SwapByte(W25Q64_DUMMY_BYTE);//厂商ID
	*DID=MySPI_SwapByte(W25Q64_DUMMY_BYTE);//寄存器ID
	 *DID<<=8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	 MySPI_End();
}

void W25Q64_WriteEnable(void){
	 MySPI_Start();
	 MySPI_SwapByte(W25Q64_WRITE_ENABLE);//使能指令
	 MySPI_End();
}

void W25Q64_WaitBusy(void){
	uint32_t TimeOut=0;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);//读状态寄存器1
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE)&0x01)==0x01){ //防止死循环卡死
		TimeOut++;
		if(TimeOut>100000){
			break;
		}
	}//等待状态寄存器不为忙
	MySPI_End();
}

void W25Q64_PagePRogram(uint32_t Address,uint8_t *DataArray,uint16_t Count){//页编程
	 W25Q64_WriteEnable();
	
	 uint16_t i=0;
	 MySPI_Start();
	 MySPI_SwapByte(W25Q64_PAGE_PROGRAM);//页编程的指令
	 MySPI_SwapByte(Address>>16); //从高位开始依次给从机发送24位地址
	 MySPI_SwapByte(Address>>8);
	 MySPI_SwapByte(Address);
	 for(i=0;i<Count;i++)
	 {
	   MySPI_SwapByte(DataArray[i]);
	 }
	 
	 MySPI_End(); 
	 W25Q64_WaitBusy();
	 
	
	
								
}

void W25Q64_SectorErase(uint32_t Address){//扇区擦除
	 W25Q64_WriteEnable();
	 
	 MySPI_Start();
	 MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	 MySPI_SwapByte(Address>>16); //从高位开始依次给从机发送24位地址
	 MySPI_SwapByte(Address>>8);
	 MySPI_SwapByte(Address);
	 MySPI_End();
	 W25Q64_WaitBusy();	
	
}

void  W25Q64_ReadData(uint32_t Address,uint8_t *DataArray,uint32_t count){
	 uint32_t i;
	
	 MySPI_Start();
	 MySPI_SwapByte(W25Q64_READ_DATA);
	 MySPI_SwapByte(Address>>=16); //从高位开始依次给从机发送24位地址
	 MySPI_SwapByte(Address>>=8);
	 MySPI_SwapByte(Address);
	 for(i=0;i<count;i++){
		DataArray[i]=MySPI_SwapByte(W25Q64_DUMMY_BYTE);
		
	 }
	 
	 MySPI_End();
     W25Q64_WaitBusy();//判断是否忙
}

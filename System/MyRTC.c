#include "stm32f10x.h"                  // Device header
#include <time.h>
uint16_t MyRTC_Time[]={2023,1,1,23,59,55};

void MyRTC_SetTime();
void MyRTC_Init(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	if(BKP_ReadBackupRegister(BKP_DR1)!=0xA5A5){
	RCC_LSEConfig(RCC_LSE_ON); //时钟的选择
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)!=SET);   //等待时钟开启
	
	
	//选择时钟源       U
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);//使能时钟
	
	RTC_WaitForSynchro();//等待同步
	RTC_WaitForLastTask();//等待上一次写入完成
	
	
	RTC_SetPrescaler(40000-1);   //配置预分频器
	RTC_WaitForLastTask();//等待上一次写入完成
	
	RTC_SetCounter(0);//设置初始时间
	RTC_WaitForLastTask();//等待上一次写入完成
	MyRTC_SetTime();	
	BKP_WriteBackupRegister(BKP_DR1,0xA5A5);
	}
	 else{
	    RTC_WaitForSynchro();//等待同步
	    RTC_WaitForLastTask();//等待上一次写入完成	 
		 
	 }
}

void MyRTC_SetTime(){//把数组时间，转换为秒数，写到cnt中
	time_t time_cnt;
	struct tm time_data;
	
	time_data.tm_year=MyRTC_Time[0]-1900;
	time_data.tm_mon=MyRTC_Time[1]-1;
	time_data.tm_mday=MyRTC_Time[2];
	time_data.tm_hour=MyRTC_Time[3];
	time_data.tm_min=MyRTC_Time[4];
	time_data.tm_sec=MyRTC_Time[5];
	
	time_cnt=mktime(&time_data)-8*60*60;
	RTC_SetCounter(time_cnt);
	RTC_WaitForLastTask();//等待上一次写入完成
	
}


void MyRTC_ReadTime(){
	time_t time_cnt;
	struct tm time_data;
	
	time_cnt=RTC_GetCounter()+8*60*60;
	time_data=*localtime(&time_cnt);
	
	MyRTC_Time[0]=time_data.tm_year+1900;
	MyRTC_Time[1]=time_data.tm_mon+1;
	MyRTC_Time[2]=time_data.tm_mday;
	MyRTC_Time[3]=time_data.tm_hour;
	MyRTC_Time[4]=time_data.tm_min;
	MyRTC_Time[5]=time_data.tm_sec;
}

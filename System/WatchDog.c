#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"

void WatchDog_Init(){
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST)==SET)
	{
		OLED_ShowString(3,1,"IWDGRST");
		Delay_ms(500);
		OLED_ShowString(3,1,"       ");
		Delay_ms(100);
		
		RCC_ClearFlag();//看门狗标志位清除
		
	}
	else
	{
		OLED_ShowString(2,1,"RST");
		Delay_ms(500);
		OLED_ShowString(2,1,"       ");
		Delay_ms(100);
		
	}
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//解除写保护
	IWDG_SetPrescaler(IWDG_Prescaler_16);//选择预分频
	IWDG_SetReload(2499); //重装值      计算超时时间
	IWDG_ReloadCounter();//喂狗
	IWDG_Enable();//
}


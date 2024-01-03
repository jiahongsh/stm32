#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"



int main(void){
	Buzzer_Init();
	LightSensor_Init();
	while(1){
	
      if(LightSensor_Get()==1){
		  Buzzer_ON(GPIO_Pin_12);
	  }	
       else{
		   Buzzer_OFF(GPIO_Pin_12);
       }		   
	  
	}
}

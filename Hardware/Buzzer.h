#ifndef __BUZZER_H
#define __BUZZER_H

void Buzzer_Init(void);
void Buzzer_ON(uint16_t GPIO_Pin);
void Buzzer_OFF(uint16_t GPIO_Pin);
void Buzzer_Turn(uint16_t GPIO_Pin);

#endif

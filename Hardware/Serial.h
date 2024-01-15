#ifndef __SERIAL_H
#define __SERIAL_H

#include<stdio.h>
void Serial_Init();
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t*Array,uint16_t Length);
void Serial_SendString(uint8_t*String);
void Serial_SendNumber(uint32_t Number,uint16_t Length);
int fputc(int ch,FILE* f);
void Serial_Print(char*format,...);
uint8_t Serial_GetFlag(void);
uint8_t Serial_GetData(void);
#endif

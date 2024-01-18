#include "stm32f10x.h"                  // Device header
#include "MyIIC.h" 
#include "MPU6050Reg.h"
#define MPU6050_Address 0xD0

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data){//指定地址写寄存器
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_Address);
	MyI2C_ReceiveAck();//此处判断是否应答
    MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();//此处判断是否应答
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress){
	uint8_t Data;
	//设置当前地址指针
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_Address);
	MyI2C_ReceiveAck();//此处判断是否应答
    MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();//此处判断是否应答
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_Address |0x01);//开启读从机的时序
	MyI2C_ReceiveAck();
	Data=MyI2C_ReceiveByte();
	MyI2C_SendByAck(1);//高电位，不接收应答
	MyI2C_Stop();
     return Data;
}

void MPU6050_Init(){
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x00);//电源管理寄存器1
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);//采样率分频，决定数据输出的快慢，越小越快
	MPU6050_WriteReg(MPU6050_CONFIG,0x06); //配置寄存器 ,数字低通滤波器拉满
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);//陀螺仪配置寄存器
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);//加速度计最大量程
	
}

void MPU6050_GetData(int16_t* AccX,int16_t* AccY,int16_t* AccZ,int16_t* GyroX,int16_t* GyroY,int16_t* GyroZ){
	uint8_t DataH,DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	 *AccX=(DataH<<8)|DataL;
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	 *AccY=(DataH<<8)|DataL;
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	 *AccZ=(DataH<<8)|DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX=(DataH<<8)|DataL;
	DataH=MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY=(DataH<<8)|DataL;
	DataH=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ=(DataH<<8)|DataL;
}

uint8_t MPU6050_GetID(){
	
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}


uint8_t MPU6050_Temp(){
	uint8_t temp;
	uint8_t DataH=MPU6050_ReadReg(MPU6050_TEMP_OUT_H);
    uint8_t	DataL=MPU6050_ReadReg(MPU6050_TEMP_OUT_L);
	 temp=(DataH<<8)|DataL;
	return (temp/340.0 + 36.53);
}
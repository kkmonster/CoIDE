
#include "cmsis_boot/stm32f10x.h"
#include "cmsis_boot/stm32f10x_conf.h"
#include "mpu6050_lib/MPU6050.h"
#include "user_setup/user_initial.h"






void delay (vu32 ms)
{
	while(ms--)
	{
		vu32 count=5525;
		while(count--);
	}
}

s16 buffer[6];

int main(void)
{

//	enable iic
	MPU6050_I2C_Init();
//	enable mpu6050
	MPU6050_Initialize();
//	enable DLF MPU6050_DLPF_BW_xx
//    MPU6050_SetDigitalLowPassFilter((u8)MPU6050_DLPF_BW_42) ;
//    MPU//6050_SetDigitalLowPassFilter((u8) 0x03);
    while(1)
    {
    	MPU6050_GetRawAccelGyro(buffer) ;
//    	delay(10);
    }
}

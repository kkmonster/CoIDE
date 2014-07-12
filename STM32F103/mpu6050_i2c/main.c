
#include "cmsis_boot/stm32f10x.h"
#include "cmsis_boot/stm32f10x_conf.h"
#include "mpu6050_lib/MPU6050.h"

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
	MPU6050_I2C_Init();
	MPU6050_Initialize();

    while(1)
    {
    	MPU6050_GetRawAccelGyro(buffer) ;
    	delay(1);
    }
}

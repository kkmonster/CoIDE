
#include "mpu6050_lib/MPU6050.h"
#include "mpu6050_lib/bool.h"
#include "cmsis_boot/stm32f4xx.h"
#include "cmsis_boot/stm32f4xx_conf.h"

void delay(u32 millisec)
{
	while(millisec --);
}

s16 buffer[6] ;

int main(void)
{
	MPU6050_I2C_Init() ;
	MPU6050_Initialize();

    while(1)
    {
    	MPU6050_AccelGyro(&buffer);
    	delay(100);
    }
}

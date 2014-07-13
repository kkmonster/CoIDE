
#include "cmsis_boot/stm32f10x.h"
#include "cmsis_boot/stm32f10x_conf.h"
#include "mpu6050_lib/MPU6050.h"
#include "user_setup/user_initial.h"

s16 buffer[6];

void systick_init()
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(9000);   // 9,000,000 / sampling loop
	NVIC_SetPriority(SysTick_IRQn,1);

}

void SysTick_Handler(void)
{
	MPU6050_GetRawAccelGyro(buffer) ;
}

int main(void)
{

	MPU6050_I2C_Init();
	DMA_setup();		// setup dma for i2c
	MPU6050_Initialize();
	systick_init();

    while(1)
    {


    }
}

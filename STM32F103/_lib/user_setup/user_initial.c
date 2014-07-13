#include "cmsis_boot/stm32f10x.h"
#include "cmsis_boot/stm32f10x_conf.h"
#include "../mpu6050_lib/MPU6050.h"

#define I2C1_DR_Address        0x40005410
#define I2C2_DR_Address        0x40005810
#define BufferSize             6

uint16_t I2C2_Buffer_Rx[BufferSize];

void DMA_setup()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_InitTypeDef  DMA_InitStructure;

	  /* DMA1 channel5 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel5);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)I2C2_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)I2C2_Buffer_Rx;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = BufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);

	I2C_DMACmd(I2C2, ENABLE);

	DMA_Cmd(DMA1_Channel5, ENABLE);
}

void MPU6050_I2C_Init()
{
  I2C_InitTypeDef  I2C_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable I2C and GPIO clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  /* Configure I2C pins:       |     SCL     |    SDA    |*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(MPU6050_I2C_Port, &GPIO_InitStructure);

  /* I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = MPU6050_DEFAULT_ADDRESS; // MPU6050 7-bit adress = 0x68, 8-bit adress = 0xD0;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = 400000;// 400kHz fast mode

  /* Apply I2C configuration after enabling it */
  I2C_Init(I2C2, &I2C_InitStructure);
  /* I2C Peripheral Enable */

//  I2C_DMALastTransferCmd(I2C2,ENABLE);
  I2C_Cmd(I2C2, ENABLE);
}



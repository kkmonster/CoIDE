
	#include "stm32f10x_conf.h"
	#include "stm32f10x.h"
	/*============================================*/

	void init_gpio_ain(){

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);

		GPIO_InitTypeDef init_gpio;
		init_gpio.GPIO_Mode = GPIO_Mode_AIN;
		init_gpio.GPIO_Pin = GPIO_Pin_0;
		GPIO_Init(GPIOA,&init_gpio);

		ADC_InitTypeDef init_adc;
		init_adc.ADC_ContinuousConvMode = DISABLE ;
		init_adc.ADC_DataAlign =ADC_DataAlign_Right;
		init_adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		init_adc.ADC_Mode = ADC_Mode_InjecSimult;
		init_adc.ADC_NbrOfChannel = 1 ;
		init_adc.ADC_ScanConvMode = DISABLE;
		ADC_Init(ADC1,&init_adc);

		ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);
		ADC_Cmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetResetCalibrationStatus(ADC1));
		ADC_StartCalibration(ADC1);
		while(ADC_GetCalibrationStatus(ADC1));

	}



u16 analog_in = 0;

	int main(void)
	{

		init_gpio_ain();

		while(1)
		{
			ADC_Cmd(ADC1,ENABLE);
			while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);

				analog_in = ADC_GetConversionValue(ADC1);


		}
	}

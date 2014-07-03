#include "stm32f10x_conf.h"
#include "stm32f10x.h"


	s8 state = 0 ;
	void togle_led()
	{
		state = 1-state;
		if (state==1) {
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,SET);
		} else {
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,RESET);
		}
	}

	void init_gpio()
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

		GPIO_InitTypeDef init_gpio ;
		init_gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		init_gpio.GPIO_Pin = GPIO_Pin_0 ;
		init_gpio.GPIO_Speed = GPIO_Speed_50MHz	;
		GPIO_Init(GPIOA, &init_gpio);

		init_gpio.GPIO_Mode = GPIO_Mode_IPU;
		init_gpio.GPIO_Pin	= GPIO_Pin_1;
		GPIO_Init(GPIOA,&init_gpio);
	}


	void init_nvic()
	{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

		NVIC_InitTypeDef init_nvic ;
		init_nvic.NVIC_IRQChannel = EXTI1_IRQn ;
		init_nvic.NVIC_IRQChannelCmd = ENABLE;
		init_nvic.NVIC_IRQChannelPreemptionPriority = 0;
		init_nvic.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&init_nvic);
	}

	void init_exti()
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

		EXTI_InitTypeDef init_exti ;
		init_exti.EXTI_Line	= EXTI_Line1 ;
		init_exti.EXTI_LineCmd	=  ENABLE;
		init_exti.EXTI_Mode	=EXTI_Mode_Interrupt;
		init_exti.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_Init(&init_exti);
	}

	void EXTI1_IRQHandler()
	{
		if(EXTI_GetITStatus(EXTI_Line1)==SET){
			togle_led();
			EXTI_ClearITPendingBit(EXTI_Line1);
		}
	}


int main(void)
{
init_exti();
init_gpio();
init_nvic();


    while(1)
    {
    }
}

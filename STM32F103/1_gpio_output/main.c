#include "stm32f10x_conf.h"
#include "stm32f10x.h"

	/*===================================== delay(ms) ===========================================*/
	void delay (vu32 ms)
	{
		while(ms--)
		{
			vu32 count=5525;
			while(count--);
		}
	}
	/*===================================== Init GPIO ===========================================*/
	void init_gpio()
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

		GPIO_InitTypeDef init_gpio;
		init_gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		init_gpio.GPIO_Pin =  GPIO_Pin_0 ;
		init_gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&init_gpio);
	}

	/*===================================== togle led ===========================================*/
	s8 state = 1 ;
	void togle_led()
  {
	  state = 1-state ;
	  if (state==1) {
		  GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	}else {
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	}

  }
	int main(void)

	{	init_gpio();

		while(1)
		{

	togle_led();
	delay(1000);

			}
}

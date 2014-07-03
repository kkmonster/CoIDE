#include "stm32f10x_conf.h"
#include "stm32F10x.h"



void init_gpio(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef init_gpio ;
	init_gpio.GPIO_Mode = GPIO_Mode_IPU ;
	init_gpio.GPIO_Pin =  GPIO_Pin_1;
	init_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&init_gpio);

	init_gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	init_gpio.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&init_gpio);

}

u8 state = 1;
void togle_led(){

	state = 1-state;

	if (state==1) {
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	} else {
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	}





}








s8 data_read1=0;
s8 data_read2=0;

int main(void)
{
 init_gpio();
    while(1)
    {
    	 data_read1 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
    	if (((data_read2-data_read1)== 1)) {
			togle_led();
		}

    	 data_read2 = data_read1;


    }
}

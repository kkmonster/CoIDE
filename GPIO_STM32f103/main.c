#include "stm32f10x_conf.h"
#include "stm32f10x.h"


u8 Count=45;
u8 Count_2 =0;
void delay(u32 delay_count)
{
	while(delay_count) delay_count-- ;
}

void init_led()
{
	//enable RCC for GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	// configuration pin
	GPIO_InitTypeDef Init_gpio ;
	Init_gpio.GPIO_Pin = 0x00FF ;		// port 0-8
	Init_gpio.GPIO_Mode= GPIO_Mode_Out_OD ;
	Init_gpio.GPIO_Speed=GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA, &Init_gpio) ;
}

void Set_led(GPIO_TypeDef *GPIOx ,u16 GPIO_pin )
{
	GPIO_SetBits(GPIOx,GPIO_pin);
}

void Reset_led(GPIO_TypeDef *GPIOx,u16 GPIO_pin)
{
	GPIO_ResetBits(GPIOx,GPIO_pin);
}

int main(void)
{


init_led();

    while(1)
    {

    	Count --;
    	if (Count==0) {
			Count=150;
		}
    	Set_led(GPIOA,0x00FF);
    	delay(500000);
    	Reset_led(GPIOA,0x00FF);
    	delay(500000);
    	Count_2 = Count+3 ;
    }
}

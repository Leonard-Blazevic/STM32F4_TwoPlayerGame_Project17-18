#include <led.h>

void gpio_led_init()
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	
	//init LEDs
	RCC_AHB1PeriphClockCmd(LED3_GREEN_RCC_GPIOx, ENABLE);
	GPIO_InitStruct.GPIO_Pin		= LED3_GREEN_PinNumber;
	GPIO_InitStruct.GPIO_Mode		= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd		= GPIO_PuPd_NOPULL;
	GPIO_Init(LED3_GREEN_GPIOx, &GPIO_InitStruct);
	
	RCC_AHB1PeriphClockCmd(LED4_RED_RCC_GPIOx, ENABLE);
	GPIO_InitStruct.GPIO_Pin		= LED4_RED_PinNumber;
	GPIO_Init(LED4_RED_GPIOx, &GPIO_InitStruct);
}

void gpio_led_toggle(uint8_t LED_ID){
	switch(LED_ID)
	{
		case LED3_GREEN_ID:
			GPIO_ToggleBits(LED3_GREEN_GPIOx, LED3_GREEN_PinNumber);
			break;
		case LED4_RED_ID:
			GPIO_ToggleBits(LED4_RED_GPIOx, LED4_RED_PinNumber);
			break;
	}
}

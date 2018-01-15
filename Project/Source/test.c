#include <gyro.h>
#include <main.h>

void GpioLEDInit()
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


void LEDTest(direction test_dir)
{
		switch (test_dir) {
			case NoChange:
				STM_EVAL_LEDOff(LED3);
				STM_EVAL_LEDOff(LED4);
				break;
			case Down:
				STM_EVAL_LEDOff(LED3);
				STM_EVAL_LEDOff(LED4);
				break;
			case Left:
				STM_EVAL_LEDOn(LED3);
				STM_EVAL_LEDOff(LED4);
				break;
			case Up:
				STM_EVAL_LEDOn(LED3);
				STM_EVAL_LEDOn(LED4);
				break;
			case Right:
				STM_EVAL_LEDOff(LED3);
				STM_EVAL_LEDOn(LED4);
				break;
		}
}


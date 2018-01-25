/*----------------------------------------------------------------------------*/
//	INPUT.C
//
//	Initialize using inputInit() function.
//
//	Pressing a button loads the input buffer, which can be unloaded using the
//	popInputBuffer() function. Returned data type is button (see input.h).
//
/*----------------------------------------------------------------------------*/
#include <main.h>

/*Private variables-----------------------------------------------------------*/
static struct {
	uint32_t queue;
	uint8_t top;
} inputBuffer;
/*----------------------------------------------------------------------------*/

/*Private functions-----------------------------------------------------------*/
static void disableButtonInterrupts(void){
	NVIC_DisableIRQ(BUTTON1_NVIC_IRQChannel);
	NVIC_DisableIRQ(BUTTON2_NVIC_IRQChannel);
	NVIC_DisableIRQ(BUTTON3_NVIC_IRQChannel);
}

static void enableButtonInterrupts(void){
	NVIC_EnableIRQ(BUTTON1_NVIC_IRQChannel);
	NVIC_EnableIRQ(BUTTON2_NVIC_IRQChannel);
	NVIC_EnableIRQ(BUTTON3_NVIC_IRQChannel);
}

static void buttonInit(void){	
	
	NVIC_InitTypeDef	NVIC_InitStruct;
	EXTI_InitTypeDef	EXTI_InitStruct;
	GPIO_InitTypeDef	GPIO_InitStruct;
	
	//button 1
	GPIO_InitStruct.GPIO_Pin		= BUTTON1_PinNumber;
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Mode		= GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd		= GPIO_PuPd_NOPULL;//
	GPIO_Init(BUTTON1_GPIOx, &GPIO_InitStruct);
	
	EXTI_InitStruct.EXTI_Line		= BUTTON1_EXTI_Line;
	EXTI_InitStruct.EXTI_Mode		= EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel	= BUTTON1_NVIC_IRQChannel	;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	//NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	RCC_AHB1PeriphClockCmd(BUTTON1_RCC_GPIOx, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(BUTTON1_EXTI_PortSourceGPIOx, BUTTON1_EXTI_PinSourcex);
	
	NVIC_ClearPendingIRQ(EXTI2_IRQn);
	
	//button 2
	GPIO_InitStruct.GPIO_Pin		= BUTTON2_PinNumber;
	GPIO_Init(BUTTON2_GPIOx, &GPIO_InitStruct);
	
	EXTI_InitStruct.EXTI_Line		= BUTTON2_EXTI_Line;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel	= BUTTON2_NVIC_IRQChannel;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	
	RCC_AHB1PeriphClockCmd(BUTTON2_RCC_GPIOx, ENABLE);
	SYSCFG_EXTILineConfig(BUTTON2_EXTI_PortSourceGPIOx, BUTTON2_EXTI_PinSourcex);
	
	//button 3
	/*GPIO_InitStruct.GPIO_Pin		= BUTTON3_PinNumber;
	GPIO_Init(BUTTON3_GPIOx, &GPIO_InitStruct);
	
	EXTI_InitStruct.EXTI_Line		= BUTTON3_EXTI_Line;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel	= BUTTON3_NVIC_IRQChannel;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStruct);
	
	RCC_AHB1PeriphClockCmd(BUTTON3_RCC_GPIOx, ENABLE);
	SYSCFG_EXTILineConfig(BUTTON3_EXTI_PortSourceGPIOx, BUTTON3_EXTI_PinSourcex);*/
}

static void pushInputBuffer (button bt){
	disableButtonInterrupts();
	
	uint32_t temp = bt << inputBuffer.top;
	inputBuffer.queue |= temp;
	inputBuffer.top += 2;
	
	enableButtonInterrupts();
}


/*----------------------------------------------------------------------------*/

/*Public functions------------------------------------------------------------*/
void inputInit(void){
	//initialize buttons
	buttonInit();
	//initialize status var
	inputBuffer.queue = 0;
	inputBuffer.top = 0;
	//Enable Interrupts
	enableButtonInterrupts();
	popInputBuffer();
}

button popInputBuffer (void){
	if (!inputBuffer.top)
		return NOTPRESSED;
	
	disableButtonInterrupts();
	
	uint8_t temp = inputBuffer.queue & 0x03;
	inputBuffer.queue = inputBuffer.queue >> 2;
	if (inputBuffer.top)
		inputBuffer.top -= 2;
	
	enableButtonInterrupts();
	
	return (button)temp;
}
	


void EXTI2_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line2);
		
		pushInputBuffer(BT_1);
		//test
		/*
		gpio_led_toggle(1);
		*/
	}
}

void EXTI3_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line3) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line3);
		
		pushInputBuffer(BT_2);
		//test
		/*
		gpio_led_toggle(2);
		*/
	}
}


void EXTI4_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line4);
		
		pushInputBuffer(BT_3);
		//test
		/*
		gpio_led_toggle(1);
		gpio_led_toggle(2);
		*/
		
	}
}




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INPUT_H
#define INPUT_H

/* Comment -------------------------------------------------------------------
Button 1 - PG2
Button 2 - PG3
Button 3 - PD4

Initialize using inputInit() function.
Pressing a button loads the input buffer, which can be unloaded using the
popInputBuffer() function. Returned data type is button (see below).
------------------------------------------------------------------------------*/
typedef enum {
	NOTPRESSED = 0,
	BT_1 = 1,
	BT_2 = 2,
	BT_3 = 3,
} button;


/* Includes ------------------------------------------------------------------*/
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

/* Private functions ---------------------------------------------------------*/
static void buttonInit(void);
static void disableButtonInterrupts(void);
static void enableButtonInterrupts(void);
static void pushInputBuffer (button bt);

/* Public functions ----------------------------------------------------------*/
button popInputBuffer (void);
void inputInit(void);




/* Defines -------------------------------------------------------------------*/

#define BUTTON1_RCC_GPIOx				RCC_AHB1Periph_GPIOG
#define BUTTON2_RCC_GPIOx				RCC_AHB1Periph_GPIOG
#define BUTTON3_RCC_GPIOx				RCC_AHB1Periph_GPIOD

#define BUTTON1_GPIOx						GPIOG
#define BUTTON2_GPIOx						GPIOG
#define BUTTON3_GPIOx						GPIOD

#define BUTTON1_PinNumber				GPIO_Pin_2
#define BUTTON2_PinNumber				GPIO_Pin_3
#define BUTTON3_PinNumber				GPIO_Pin_4

//exti
#define BUTTON1_EXTI_PortSourceGPIOx		EXTI_PortSourceGPIOG
#define BUTTON2_EXTI_PortSourceGPIOx		EXTI_PortSourceGPIOG
#define BUTTON3_EXTI_PortSourceGPIOx		EXTI_PortSourceGPIOD

#define BUTTON1_EXTI_PinSourcex					EXTI_PinSource2
#define BUTTON2_EXTI_PinSourcex					EXTI_PinSource3
#define BUTTON3_EXTI_PinSourcex					EXTI_PinSource4

#define BUTTON1_EXTI_Line								EXTI_Line2
#define BUTTON2_EXTI_Line								EXTI_Line3
#define BUTTON3_EXTI_Line								EXTI_Line4

//nvic
#define BUTTON1_NVIC_IRQChannel					EXTI2_IRQn
#define BUTTON2_NVIC_IRQChannel					EXTI3_IRQn
#define BUTTON3_NVIC_IRQChannel					EXTI4_IRQn


#endif

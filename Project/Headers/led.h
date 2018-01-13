/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LED_H
#define LED_D

/* Comment -------------------------------------------------------------------
LEDs on STM32F429I-Discovery
------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

/* Private functions ---------------------------------------------------------*/


/* Public functions ----------------------------------------------------------*/
void gpio_led_toggle(uint8_t LED_ID);
void gpio_led_init(void);

/* Defines -------------------------------------------------------------------*/
#define LED3_GREEN_RCC_GPIOx		RCC_AHB1Periph_GPIOG
#define LED4_RED_RCC_GPIOx			RCC_AHB1Periph_GPIOG

#define	LED3_GREEN_GPIOx				GPIOG
#define	LED4_RED_GPIOx					GPIOG

#define LED3_GREEN_PinNumber		GPIO_Pin_13
#define LED4_RED_PinNumber			GPIO_Pin_14

#define LED3_GREEN_ID						1
#define LED4_RED_ID							2


#endif

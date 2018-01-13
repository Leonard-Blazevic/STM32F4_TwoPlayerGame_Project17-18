#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <misc.h>
#include <stm32f4xx_syscfg.h>
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_l3gd20.h"

#define LED3_GREEN_RCC_GPIOx		RCC_AHB1Periph_GPIOG
#define LED4_RED_RCC_GPIOx			RCC_AHB1Periph_GPIOG

#define	LED3_GREEN_GPIOx				GPIOG
#define	LED4_RED_GPIOx					GPIOG

#define LED3_GREEN_PinNumber		GPIO_Pin_13
#define LED4_RED_PinNumber			GPIO_Pin_14


#define L3G_Sensitivity_250dps     (float)114.285f        
#define L3G_Sensitivity_500dps     (float)57.1429f        
#define L3G_Sensitivity_2000dps    (float)14.285f

void gyro_init(void);
uint8_t get_direction(void);
void gpio_led_init(void);
void read_ang_rate (float* pfData);
void LEDTest (uint8_t test_dir);

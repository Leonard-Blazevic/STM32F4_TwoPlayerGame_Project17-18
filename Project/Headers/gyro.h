#include <stm32f4xx_gpio.h>
#include <lcdfunctions.h>

#define LED3_GREEN_RCC_GPIOx		RCC_AHB1Periph_GPIOG
#define LED4_RED_RCC_GPIOx			RCC_AHB1Periph_GPIOG

#define	LED3_GREEN_GPIOx				GPIOG
#define	LED4_RED_GPIOx					GPIOG

#define LED3_GREEN_PinNumber		GPIO_Pin_13
#define LED4_RED_PinNumber			GPIO_Pin_14


#define L3G_Sensitivity_250dps     (float)114.285f        
#define L3G_Sensitivity_500dps     (float)57.1429f        
#define L3G_Sensitivity_2000dps    (float)14.285f
	
#define GyroSampleNum						1000
	
#define Xangle_down							50
#define Xangle_up								-50
#define Yangle_left							50
#define Yangle_right						-50


void GyroInit(void);
Direction GetDirection(void);
void ReadAngRate (float* GyroData);

#include <stm32f4xx_gpio.h>

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
	
#define Xangle_down							2000
#define Xangle_up								-2000
#define Yangle_left							2000
#define Yangle_right						-2000

#define Xrate_down							10
#define Xrate_up								-10
#define Yrate_left							10
#define Yrate_right							-10


typedef enum {
	NoChange = 0,
	Down = 1,
	Left = 2,
	Up = 3,
	Right = 4,
} direction;


void GyroInit(void);
direction GetDirection(void);
void GpioLEDInit(void);
void ReadAngRate (float* GyroData);
void LEDTest (direction test_dir);

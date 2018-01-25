#ifndef WIRELESSSERIALCOMMUNICATION_H

#define WIRELESSSERIALCOMMUNICATION_H

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>  
#include <stm32f4xx_usart.h> 

#define BUFSIZE        16 
#define BAUDRATE       115200      //DON'T CHANGE - default baudrate for ESP
#define CONNECTED      '2'

typedef enum{
	
	TRUE = 1,
	FALSE = 0,
	
} Boolean;

typedef struct {
	
	int sync;
	Direction movement;
	Boolean hasFired;
	Boolean readFlag;
	
} WifiPackage;


void Usart1GpioInit(void);
void EspSync(void);
void SendData(WifiPackage struct1);
void ReadData(WifiPackage *struct1);

#endif

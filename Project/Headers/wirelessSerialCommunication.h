#ifndef WIRELESSSERIALCOMMUNICATION_H

#define WIRELESSSERIALCOMMUNICATION_H

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>  
#include <stm32f4xx_usart.h> 

#define BUFSIZE       16 
#define BAUDRATE      115200      //DON'T CHANGE - default baudrate for ESP
#define STOPSIGN      '}'         //ESP will read from serial interface until it reaches STOPSIGN - STOPSIGN WON'T BE READ!

void Usart1GpioInit(void);
void SendData(Struct struct1);
Struct ReadData(void);


#endif

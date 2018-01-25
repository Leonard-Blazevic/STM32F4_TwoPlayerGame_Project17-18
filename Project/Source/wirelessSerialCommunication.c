
/*----------------------------------------------------------------------------*/
//	wirelessSerialCommunication.c
//
//	Initialize using Usart1GpioInit() function then sync ESP's by calling EspSync()
//
//	Reads and writes 4 integers from struct
//  defined in header file to/from serial interface (UART)
/*----------------------------------------------------------------------------*/
#include "main.h"

/*Private variables-----------------------------------------------------------*/
static char receiveBuffer[BUFSIZE];
static int rxHead, rxTail;
static uint8_t TxReady;
/*----------------------------------------------------------------------------*/


/*Private functions-----------------------------------------------------------*/
static void InitEspResetPin(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;   //red LED
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	GPIO_SetBits(GPIOG, GPIO_Pin_14);   //set PG_14 high (turned on)
}

 static void WriteByteToSerial(char c)
{
	while(!TxReady);
	USART_SendData(USART1, c);
	TxReady = 0;
}

static char PopReceiveBuffer(void)
{
	char c='x';                                   //'x' marks that nothing was read from the bufffer
	
	NVIC_DisableIRQ(USART1_IRQn);
	
	if(rxHead != rxTail)
  {
		c = receiveBuffer[rxHead];
		rxHead++;
		
		if(rxHead == BUFSIZE)
		  rxHead = 0;
	}
	
	NVIC_EnableIRQ(USART1_IRQn);
	
	return c;
}
/*----------------------------------------------------------------------------*/

/*Public functions------------------------------------------------------------*/
void Usart1GpioInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;
  NVIC_InitTypeDef NVIC_InitStructure;
	
  //enable peripheral clocks
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//setting GPIO pins
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;  //Pin PA9 (USART1_TX), pin PA10 (USART1_RX)
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	//setting UART
	USART_InitStruct.USART_BaudRate = BAUDRATE;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	USART_Init(USART1, &USART_InitStruct);
	
	//setting flags that will trigger UART IRQ
  USART_ITConfig(USART1, USART_IT_TC, ENABLE);           //transmission complete  flag
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);         //received data ready to be read flag
	
	//UART ready to receive and transmit
	TxReady = 1;
  rxHead = 0; rxTail = 0;
	
 //prepare NVIC to receive USART1 IRQs
 NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; // configure USART1 interrupts
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// max. priority
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // max. priority
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // enable USART1 interrupt in NVIC
 NVIC_Init(&NVIC_InitStructure); // set NVIC for USART1 IRQ
 
 USART_Cmd(USART1, ENABLE);  //enable interrupts
 
}

void EspSync(void)
{
  char c;
	WifiPackage syncPackage, syncReceive;
	
	InitEspResetPin();
	
	//reset ESP
	Delay(5000000);
	GPIO_ResetBits(GPIOG, GPIO_Pin_14); //set ESP_RST low
	Delay(5000000);                     //using Delay() to actually see when reset happens
	GPIO_SetBits(GPIOG, GPIO_Pin_14);   //set ESP_RST high
	
	Write("Connecting...", 0);

	syncPackage.sync = 98;

	while(1)
  {
		c=PopReceiveBuffer();
		if(c==CONNECTED)
			break;
	}
	while((c=PopReceiveBuffer()) != 'x'); //flushing buffer
	
	
#ifdef CLIENT
	ReadData(&syncReceive);
	SendData(syncReceive);
#endif
	
#ifndef CLIENT
	SendData(syncPackage);
	ReadData(&syncReceive);
#endif

  if(syncReceive.sync == 98 && syncReceive.readFlag == TRUE)
	{
		ClearScreen();
		Write("Connected!", 0);
		Write("Sync done!", 1);
	}
	
	while((c=PopReceiveBuffer()) != 'x'); //flushing buffer
	
}

void SendData(WifiPackage struct1)  
{
	
	WriteByteToSerial((char)struct1.sync);
	WriteByteToSerial((char)struct1.movement);
	WriteByteToSerial((char)struct1.hasFired);
	WriteByteToSerial((char)struct1.hp1);
	WriteByteToSerial((char)struct1.hp2);
	
   
}

void ReadData(WifiPackage *struct1)
{
    
    struct1->readFlag = FALSE;
    
    char c;
    
    while (1) {
        c = PopReceiveBuffer();
        if (c != 'x')
            break;
    }
    struct1->sync = (int) c;		

    while (1) {
        c = PopReceiveBuffer();
        if (c != 'x')
            break;
    }
    struct1->movement = (Direction) c;
		
    while (1) {
        c = PopReceiveBuffer();
        if (c != 'x')
            break;
    }
    struct1->hasFired = (Boolean) c;
		
		while (1) {
        c = PopReceiveBuffer();
        if (c != 'x')
            break;
    }
    struct1->hp1 = (int) c;
   
		while (1) {
        c = PopReceiveBuffer();
        if (c != 'x')
            break;
    }
    struct1->hp2 = (int) c;
		
    struct1->readFlag = TRUE;
}
/*----------------------------------------------------------------------------*/


/*Interrupt functions------------------------------------------------------------*/
void USART1_IRQHandler(void)
{
	static char rxChar; 
	static char rxIrqTail;
	
	//rx event
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
  {
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		rxChar = USART_ReceiveData(USART1);
		rxIrqTail = rxTail + 1;
		
		if(rxIrqTail == BUFSIZE)
			rxIrqTail = 0;
		
		if(rxIrqTail != rxHead)
    {
			receiveBuffer[rxTail] = rxChar;
			rxTail = rxIrqTail;
		}
	}
	
	//tx event
	if(USART_GetITStatus(USART1, USART_IT_TC) == SET)
  {
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		TxReady = 1;
	}
}
/*----------------------------------------------------------------------------*/


#include "main.h"

int main(void){
	
	
	WifiPackage s2, s1;
	
	Usart1GpioInit();
	StartScreen();
	ClearScreen();
	
	s1.sync = 97;
	s1.movement = 48;
	s1.hasFired = 50;
	s1.readFlag = FALSE;
	SendData(s1);
	Write("Test", 4);
	
	while(1)
	{
		
		SendData(s1);
		Delay(100000000);
		s2=ReadData();
		if(s2.readFlag == TRUE)
    {
			Write("Primljen podatak!", (s2.hasFired-48));
			Write("Usao u if", 5);
		}

		
	}
	
	/*int postojiMetak = 0, random1, random2, gameRunning=1;
	Position player1, player2;
	Queue queue;
	
	queue.end = -1; 
	queue.top = -1;
	
	if (SysTick_Config(SystemCoreClock / 1000))
  { 
		//handle errors
    while (1);
  }
	
	StartGame();
	
	player1 = TankInit(0);
	player2 = TankInit(1);
	
	Delay(TICK_RATE);
	
  while(gameRunning == 1){
		random1 = rand()%5;
		random2 = rand()%5;
		
		if (queue.end > -1 && queue.top > -1){
			BulletCycle(&queue);
		}
		
		ReadFireButton();
		ReadESP();
			
		BulletCycle(&queue);
		TankCycle(random1, random2, &player1, &player2, &queue, &postojiMetak);
			
		WriteESP();

		CheckEndGameCondition(&gameRunning);
		
		Delay(TICK_RATE);
	}
	
	EndGame();
	
	while(1);*/
}

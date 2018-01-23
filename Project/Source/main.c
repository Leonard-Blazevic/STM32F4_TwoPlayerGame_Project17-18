#include "main.h"

int main(void){
	
	
	WifiPackage s1;
	int i;
	
	Usart1GpioInit();
	StartScreen();
	ClearScreen();
	EspSync();
	
	s1.sync = 97;
	s1.movement = 48; 
	s1.readFlag = FALSE;
	s1.hasFired = 15;
	SendData(s1);
	Write("Pocetak", 1);
	Delay(100000000);
	
	while(1)
	{
		
		for(i=0; i<=12; i++)
		{
			Delay(50000000); 
			s1.hasFired = i;
			SendData(s1);
			Write("Poslano", i);
			
		}
		
		ClearScreen();

		
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

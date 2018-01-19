#include "main.h"
int main(void){
	int postojiMetak = 0, random1, random2, gameRunning=1;
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
	
	while(1);
}

#include "main.h"
int main(void){
	int random1, random2, gameRunning=1;
	Position player1, player2;
	Queue bulletQueuePlayer1, bulletQueuePlayer2;
	
	initQueue(&bulletQueuePlayer1);
	initQueue(&bulletQueuePlayer2);
	
	srand(21);
	
	StartGame();
	
	player1 = TankInit(0);
	player2 = TankInit(1);
	
	Delay(TICK_RATE);
	
	GyroInit(); 
	
  while(gameRunning){
		random1 = rand()%5;
		random2 = rand()%5;
		
		BulletCycle(&bulletQueuePlayer1);
		BulletCycle(&bulletQueuePlayer2);

		ReadFireButton();
		ReadESP();
			
		TankCycle(random1, random2, &player1, &player2, &bulletQueuePlayer1, &bulletQueuePlayer2);
			
		WriteESP();

		CheckEndGameCondition(&gameRunning);
		
		score(1, 0);
		
		GyroInit(); 
		
		random1 = GetDirection();
		
		//TankCycle(random1, random2, &player1, &player2, &bulletQueuePlayer1, &bulletQueuePlayer2);
		
		Delay(TICK_RATE);
		
	}
	
	EndGame();
	
	while(1);
}

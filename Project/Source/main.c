#include "main.h"
int main(void){
	int postojiMetak = 0, random1, random2, gameRunning=1;
	Position player1, player2;
	Queue queue;
	
	queue.end = -1; 
	queue.top = -1;

	GyroInit(); 
	
	StartGame();
	
	player1 = TankInit(0);
	player2 = TankInit(1);
	
	Delay(TICK_RATE);
	
  while(gameRunning){
		random1 = rand()%5;
		random2 = rand()%5;
		
		if (queue.end > -1 && queue.top > -1){
			BulletCycle(&queue);
		}
		
		ReadFireButton();
		ReadESP();
			
		TankCycle(random1, random2, &player1, &player2, &queue, &postojiMetak);
			
		WriteESP();

		CheckEndGameCondition(&gameRunning);
		
		Delay(10000); //ako mislis da je presporo ili prebrzo promijeni vrijeme cekanja
	}
	
	EndGame();
	
	while(1);
}

#include "main.h"

int main(void){
	int gameRunning=1, health1=initialHealth, health2=initialHealth;
	Position player1, player2;
	Queue bulletQueuePlayer1, bulletQueuePlayer2;
	WifiPackage s1, s2;
	
	s2.movement = NOCHANGE;
	s2.hasFired = FALSE;
	
	Usart1GpioInit();
	StartScreen();
	ClearScreen();
	EspSync();
	Delay(100000000);
	Write("Begin", 4);
	
	initQueue(&bulletQueuePlayer1);
	initQueue(&bulletQueuePlayer2);
	
	StartGame();
	
	player1 = TankInit(0);
	player2 = TankInit(1);
	
	Delay(TICK_RATE);
	
	GyroInit(); 
	
	srand(71);
	
  while(gameRunning){
	
		BulletCycle(&bulletQueuePlayer1, player1, player2, &health2);
		BulletCycle(&bulletQueuePlayer2, player2, player1, &health1);

		ReadFireButton();
		
#ifdef CLIENT
		ReadData(&s2);
#endif 
		
		TankCycle(random1, &s1, s2, &player1, &player2, &bulletQueuePlayer1, &bulletQueuePlayer2);
		
		SendData(s1);
		
#ifndef CLIENT
		ReadData(&s2);
#endif 

		CheckEndGameCondition(&gameRunning, health1, health2);
		score(health1, health2);
		
		Delay(TICK_RATE);
	}
	SendData(s1);
	EndGame(health1>health2);

	while(1);
}

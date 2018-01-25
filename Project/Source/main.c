#include "main.h"

int main(void){
	int random1, gameRunning=1, health1=initialHealth, health2=initialHealth;
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
	
	srand(13);
	
	StartGame();
	
	player1 = TankInit(0);
	player2 = TankInit(1);
	
	Delay(TICK_RATE);
	
	GyroInit(); 
	
	srand(1371);
	
  while(gameRunning){
		random1 = rand()%5;
		
		BulletCycle(&bulletQueuePlayer1, player1, player2, &health2);
		BulletCycle(&bulletQueuePlayer2, player2, player1, &health1);

		ReadFireButton();
		ReadESP();
		
#ifdef CLIENT
		ReadData(&s2);
#endif 
		
		TankCycle(random1, &s1, s2, &player1, &player2, &bulletQueuePlayer1, &bulletQueuePlayer2);
		
#ifdef CLIENT
		s1.hP1 = health1;
		s1.hP2 = health2;
#endif 
		
		SendData(s1);
		
#ifndef CLIENT
		ReadData(&s2);
#endif 
			
		WriteESP();
	
#ifdef CLIENT
		CheckEndGameCondition(&gameRunning, s2.hP1, s2.hP2);
		score(s2.hP1, s2.hP2);
#endif 

#ifndef CLIENT
		CheckEndGameCondition(&gameRunning, health1, health2);
		score(health1, health2);
#endif
		
		Delay(TICK_RATE);
	}
	
	EndGame(health1>health2);
	
	while(1);
}

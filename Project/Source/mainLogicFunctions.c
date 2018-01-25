#include "main.h"

static __IO uint32_t TimingDelay;

void Delay(__IO uint32_t nTime){ 
  /*TimingDelay = nTime;
  while(TimingDelay != 0);*/
	
	while(nTime != 0) nTime--;
}

void TimingDelay_Decrement(void){
  if (TimingDelay != 0)
  { 
    TimingDelay--;
  }
}

void StartGame(){
	StartScreen();
	Delay(TICK_RATE);
	ClearScreen();
}

void BulletCycle(Queue *queue, Position player, Position opponent, int *playerhealth){
	BulletPosition temp;
	Atom *top;
	top = queue->top;
	
	while(top){
		if(BulletMove(&top->element, player, opponent) == 1){
			Remove(&temp, queue);
			(*playerhealth)--;
		}
		
		top->element.life--;
		top = top->next;
	}
			
	if (queue->top->element.life < 0){
		Remove(&temp, queue);
		BulletRemove(temp, player, opponent);
	}
}

void TankCycle(int random1, WifiPackage *package1, WifiPackage package2, Position *player1, Position *player2, Queue *queue1, Queue *queue2){
	BulletPosition temp;
	//int movement=0;
	int rnd=0;
	
	//movement = GetDirection();
	
	(*package1).movement = NOCHANGE;
	(*package1).hasFired = FALSE;
	(*package1).sync = 0;
	
	switch(random1){
			case 0:
			case 1:
			case 2:
				TankMove(player1, player2, 0);
				(*package1).movement = UP;
				break;
			case 3:
				temp = BulletInit(*player1);
				if(temp.life > 0)
					Add (temp, queue1);
				(*package1).hasFired = TRUE;
				break;
			case 4:
				rnd=rand()%2;
				TankRotate(player1, rnd, 0);
			  (*package1).movement = rnd == 0 ? RIGHT : LEFT;
				break;
		}
		
		switch(package2.movement){
			case UP:
				TankMove(player2, player1, 1);
				break;
			case RIGHT:
				TankRotate(player2, 0, 1);
				break;
			case LEFT:
				TankRotate(player2, 1, 1);
				break;
			default:
				break;
		}
		
		if(package2.hasFired){
			temp = BulletInit(*player2);
			if(temp.life > 0)
				Add (temp, queue2);
		}
}

void ReadFireButton(){
	
}

void ReadESP(){
	
}

void WriteESP(){
	
}

void CheckHit(){
	
}

void CheckEndGameCondition(int *gameRunning, int health1, int health2){
	if(health1 <= 0 || health2 <= 0)
		(*gameRunning) = 0;
}

void EndGame(int winner){
	ClearScreen ();
	EndScreen(winner);
}

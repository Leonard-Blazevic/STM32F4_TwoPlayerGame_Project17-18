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

void TankCycle(int random1, int random2, Position *player1, Position *player2, Queue *queue1, Queue *queue2){
	BulletPosition temp;
	int movement=0;
	
	movement = GetDirection();
		TankRemove(*player1);
	
	switch(movement){
			case NOCHANGE:
				break;
			case 1:
				player1->direction=UP;
				break;
			case 2:
				player1->direction=RIGHT;
				break;
			case 3:
				player1->direction=DOWN;
				break;
			case 4:
				player1->direction=LEFT;
				break;
		}
	
		TankMove(player1, player2, 0);
	

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

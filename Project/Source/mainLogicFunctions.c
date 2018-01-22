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

void BulletCycle(Queue *queue){
	BulletPosition temp;
	Atom *top;
	top = queue->top;
	
	while(top){
		BulletMove(&top->element);
		top->element.life--;
		top = top->next;
	}
			
	if (queue->top->element.life < 0){
		Remove(&temp, queue);
		BulletRemove(temp);
	}
}

void TankCycle(int random1, int random2, Position *player1, Position *player2, Queue *queue1, Queue *queue2){
	BulletPosition temp;
	//int movement=0;
	
	//movement = GetDirection();
	
	switch(random1){
			case 0:
			case 1:
			case 2:
				TankMove(player1, player2, 0);
				break;
			case 3:
				temp = BulletInit(*player1);
				if(temp.life > 0)
					Add (temp, queue1);
				break;
			case 4:
				TankRotate(player1, rand()%2, 0);
				break;
		}
	
	/*switch(movement){
			case 0:
				break;
			case 1:
				TankMove(player1, player2, 0);
				break;
			case 2:
				TankRotate(player1, 0, 0);
				break;
			case 3:
				TankRotate(player1, 1, 0);
				break;
			case 4:
				break;
		}*/
	
		//TankMove(player1, player2, 0);

		switch(random2){
			case 0:
			case 1:
			case 2:
				TankMove(player2, player1, 1);
				break;
			case 3:
				temp = BulletInit(*player2);
				if(temp.life > 0)
					Add (temp, queue2);
				break;
			case 4:
				TankRotate(player2, rand()%2, 1);
				break;
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

void CheckEndGameCondition(int *gameRunning){
	
}

void EndGame(){
	ClearScreen ();
	EndScreen(1);
}

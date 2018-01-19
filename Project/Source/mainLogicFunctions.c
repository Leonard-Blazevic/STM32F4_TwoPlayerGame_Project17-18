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
	int i;
	BulletPosition temp;
	
	if (queue->end >= queue->top)
		for (i=queue->top + 1; i <= queue->end; i++){
			BulletMove(&queue->field[i]);
			queue->field[i].life--;
		}
		else{
			for (i=0; i <= queue->end; i++){
				BulletMove(&queue->field[i]);
				queue->field[i].life--;
			}
			for (i=queue->top + 1; i < numberOfAllowedBullets; i++){
				BulletMove(&queue->field[i]);
				queue->field[i].life--;
			}
		}
			
	if (queue->field[(queue->top + 1)%numberOfAllowedBullets].life < 0){
		Remove(&temp, queue);
		BulletRemove(temp);
	}
}

void TankCycle(int random1, int random2, Position *player1, Position *player2, Queue *queue, int *postojiMetak){
	switch(random1){
			case 0:
			case 1:
			case 2:
				TankMove(player1, 0);
				break;
			case 3:
				if (postojiMetak == 0){
					initQueue(queue);
					*postojiMetak = 1;
				}
				Add(BulletInit(*player1), queue);
				break;
			case 4:
				TankRotate(player1, rand()%2, 0);
				break;
		}
		
		switch(random2){
			case 0:
			case 1:
			case 2:
				TankMove(player2, 1);
				break;
			case 3:
				if (postojiMetak == 0){
					initQueue(queue);
					*postojiMetak = 1;
				}
				Add (BulletInit(*player2), queue);
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

void CheckEndGameCondition(){
	
}

void EndGame(){
	ClearScreen ();
	EndScreen(1);
}

#include "main.h"

static __IO uint32_t TimingDelay;
static int fireLimit = 10;

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
	Delay(50000000);
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

void TankCycle(int *health1, int *health2, WifiPackage *package1, WifiPackage package2, Position *player1, Position *player2, Queue *queue1, Queue *queue2){
	BulletPosition temp;
	int movement=0;
	fireLimit--;
	
	movement = GetDirection();
	
	(*package1).movement = NOCHANGE;
	(*package1).hasFired = FALSE;
	(*package1).sync = (*health1);
	
	TankRemove(*player1);

	switch(movement){
			case 1:
				player1->direction=DOWN;
				(*package1).movement = 1;
				break;
			case 2:
				player1->direction=RIGHT;
				(*package1).movement = 2;
				break;
			case 3:
				player1->direction=UP;
				(*package1).movement = 3;
				break;
			case 4:
				player1->direction=LEFT;
				(*package1).movement = 4;
				break;
			default:
				(*package1).movement = 0;
				break;
	}
	TankMove(player1, player2, 0);
	
	if(ReadFireButton()){
		temp = BulletInit(*player1);
    if(temp.life > 0 && fireLimit <= 0){
			Add (temp, queue1);
			(*package1).hasFired = TRUE;
			fireLimit = 10;
		}
		else
			BulletRemove(temp, *player1, *player2);
	}
	
	TankRemove(*player2);
		
	switch(package2.movement){
    case 3:
			player2->direction=DOWN;
			break;
    case 2:
			player2->direction=RIGHT;
			break;
    case 1:
			player2->direction=UP;
			break;
    case 4:
			player2->direction=LEFT;
			break;
		default:
			break;
	}
	
	TankMove(player2, player1, 1);
        
  if(package2.hasFired){
		temp = BulletInit(*player2);
    if(temp.life > 0)
			Add (temp, queue2);
		else
		BulletRemove(temp, *player1, *player2);
	}
	
	*health2 = package2.sync;
}

int ReadFireButton(){
	button tmp;
	tmp = popInputBuffer();
	switch (tmp){
		case BT_1:
			return 1;					
		case BT_2:
			return 0;
		default:
			return 0;
	}	
}

void CheckEndGameCondition(int *gameRunning, int health1, int health2){
	if(health1 <= 0 || health2 <= 0)
		(*gameRunning) = 0;
}

void EndGame(int winner){
	ClearScreen ();
	EndScreen(winner);
}

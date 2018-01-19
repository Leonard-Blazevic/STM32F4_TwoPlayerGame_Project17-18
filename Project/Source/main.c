#include "main.h"
#include <stdlib.h>

int main(void)
{
	int random1, random2, i;
	int postojiMetak = 0;
	Position player1, player2;
	Queue queue;
	BulletPosition temp;
	
	queue.end = -1; 
	queue.top = -1;
	
	StartScreen();
	
	Delay(TICK_RATE);
	
	ClearScreen();
	
	player1 = TankInit(0);
	player2 = TankInit(1);
	
	Delay(TICK_RATE);
	
  while (1){
		random1 = rand()%5;
		random2 = rand()%5;
		
		if (queue.end > -1 && queue.top > -1){
			if (queue.end >= queue.top)
				for (i=queue.top + 1; i <= queue.end; i++){
					BulletMove(&queue.field[i]);
					queue.field[i].life--;
				}
			else{
				for (i=0; i <= queue.end; i++){
					BulletMove(&queue.field[i]);
					queue.field[i].life--;
				}
				for (i=queue.top + 1; i < numberOfAllowedBullets; i++){
					BulletMove(&queue.field[i]);
					queue.field[i].life--;
				}
			}
			
			if (queue.field[(queue.top + 1)%numberOfAllowedBullets].life < 0){
				Remove(&temp, &queue);
				BulletRemove(temp);
			}
		}
		
		switch(random1){
			case 0:
			case 1:
			case 2:
				TankMove(&player1, 0);
				break;
			case 3:
				if (postojiMetak == 0){
					initQueue(&queue);
					postojiMetak = 1;
				}
				Add(BulletInit(player1), &queue);
				break;
			case 4:
				TankRotate(&player1, rand()%2, 0);
				break;
		}
		
		switch(random2){
			case 0:
			case 1:
			case 2:
				TankMove(&player2, 1);
				break;
			case 3:
				if (postojiMetak == 0){
					initQueue(&queue);
					postojiMetak = 1;
				}
				Add (BulletInit(player2), &queue);
				break;
			case 4:
				TankRotate(&player2, rand()%2, 1);
				break;
		}
		
		Delay(TICK_RATE);
	}
}


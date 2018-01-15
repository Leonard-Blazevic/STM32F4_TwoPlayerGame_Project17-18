#include "main.h"

int Remove (BulletPosition *element, Queue *queue) {
	if (queue->end == queue->top) return 0;
	queue->top++;
	queue->top %= numberOfAllowedBullets;
	*element = queue->field[queue->top];
	return 1;
}

int Add (BulletPosition element, Queue *queue) {
	if ((queue->end+1) % numberOfAllowedBullets == queue->top) return 0;
	queue->end++;
	queue->end %= numberOfAllowedBullets;
	queue->field[queue->end] = element;
	return 1;
}

void initQueue(Queue *queue){
	queue->end = 0; queue->top = 0;
}


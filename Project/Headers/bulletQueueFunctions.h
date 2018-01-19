#ifndef __BULLETQUEUEFUNCTIONS_H
#define _BULLETQUEUEFUNCTIONS_H

#define numberOfAllowedBullets 30

typedef struct {
	BulletPosition field[numberOfAllowedBullets];
	int end, top;																					//end -> ulaz, top -> izlaz
} Queue;

int Remove (BulletPosition *element, Queue *queue);
int Add (BulletPosition element, Queue *queue);
void initQueue(Queue *queue);

#endif

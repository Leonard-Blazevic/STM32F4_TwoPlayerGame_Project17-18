#ifndef __BULLETQUEUEFUNCTIONS_H
#define _BULLETQUEUEFUNCTIONS_H

struct at {
	BulletPosition element;
	struct at *next;
};
typedef struct at Atom;

typedef struct {
	Atom *end, *top;
} Queue;


int Remove (BulletPosition *element, Queue *queue);
int Add (BulletPosition element, Queue *queue);
void initQueue(Queue *queue);

#endif

#include "main.h"

void initQueue(Queue *queue){
	queue->end = NULL;
	queue->top = NULL;
}

int Add (BulletPosition element, Queue *queue) {
	Atom *created;
	if ((created = (Atom*)malloc (sizeof (Atom)))) {
		created->element = element;
		created->next = NULL;
		if (queue->top == NULL) {
			queue->top = created;		
		} else {
			(queue->end)->next = created;	
		}
		queue->end = created;
		return 1;
	}
	return 0;
}
 
int Remove (BulletPosition *element, Queue *queue) {
	Atom *old;
	if (queue->top) { 
		*element = (queue->top)->element;
		old = queue->top;
		queue->top = (queue->top)->next;
		free (old);
		if (queue->top == NULL) queue->end = NULL;
		return 1;
  }
	return 0;
}



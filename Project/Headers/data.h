#define numberOfAllowedBullets 30

typedef struct {
  int positionX;
	int positionY;
	int direction;
} PlayerPosition;

typedef struct {
  int positionX;
	int positionY;
	int direction;
	int life;
} BulletPosition;

typedef struct {
	BulletPosition field[numberOfAllowedBullets];
	int end, top;																					//end -> ulaz, top -> izlaz
} Queue;

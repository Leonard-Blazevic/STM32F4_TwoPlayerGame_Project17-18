#ifndef __LCDFUNCTIONS_H
#define __LCDFUNCTIONS_H

#include <math.h>

typedef struct {
  int positionX;
	int positionY;
	int direction;
} Position;

typedef struct {
	Position position;
	int life;
} BulletPosition;

typedef enum{
	UP = 1,
	RIGHT = 2,
	DOWN = 3,
	LEFT = 4,
	NOCHANGE = 0,
}Direction;


void StartScreen(void);
void EndScreen(int pobjednik);
Position TankInit(int choosePlayer);
BulletPosition BulletInit(Position player);
void BulletMove(BulletPosition *bullet);
void TankMove(Position *player1, Position *player2, int choosePlayer);
void TankRemove(Position player);
void BulletRemove(BulletPosition bullet);
void TankRotate(Position *player1, int next, int choosePlayer);
void score(char p1, char p2);
void ClearScreen (void);
void Write(char *p, int n);
#endif

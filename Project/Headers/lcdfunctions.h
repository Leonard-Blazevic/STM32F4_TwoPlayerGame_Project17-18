#ifndef __LCDFUNCTIONS_H
#define __LCDFUNCTIONS_H

typedef struct {
  int positionX;
	int positionY;
	int direction;
} Position;

typedef struct {
	Position position;
	int life;
} BulletPosition;

void StartScreen(void);
void EndScreen(int pobjednik);
Position TankInit(int choosePlayer);
BulletPosition BulletInit(Position player);
void BulletMove(BulletPosition *bullet);
void TankMove(Position *player1, int choosePlayer);
void TankRemove(Position player);
void BulletRemove(BulletPosition bullet);
void TankRotate(Position *player1, int next, int choosePlayer);
void score(char p1, char p2);
void ClearScreen (void);

#endif

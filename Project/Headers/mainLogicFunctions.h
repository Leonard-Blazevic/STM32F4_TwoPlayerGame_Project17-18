#ifndef __MAINLOGICFUNCTIONS_H
#define __MAINLOGICFUNCTIONS_H

#include <stdlib.h>

#define TICK_RATE 5000000

void Delay(__IO uint32_t nTime);
void StartGame(void);
void BulletCycle(Queue *queue);
void TankCycle(int random1, int random2, Position *player1, Position *player2, Queue *queue, int *postojiMetak);
void ReadFireButton(void);
void ReadGyro(void);
void ReadESP(void);
void WriteESP(void);
void CheckHit(void);
void CheckEndGameCondition(void);
void EndGame(void);

#endif
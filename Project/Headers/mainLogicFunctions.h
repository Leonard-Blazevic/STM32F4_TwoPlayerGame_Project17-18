#ifndef __MAINLOGICFUNCTIONS_H
#define __MAINLOGICFUNCTIONS_H

#include <stdlib.h>
#include "wirelessSerialCommunication.h"

#define TICK_RATE 500000
#define initialHealth 15

void Delay(__IO uint32_t nTime);
void StartGame(void);
void BulletCycle(Queue *queue, Position plyer, Position opponent, int *playerPoints);
void TankCycle(int *health1, int *health2, WifiPackage *package1, WifiPackage package2, Position *player1, Position *player2, Queue *queue1, Queue *queue2);
int ReadFireButton(void);
void CheckEndGameCondition(int *gameRunning, int points1, int points2);
void EndGame(int winner);

#endif

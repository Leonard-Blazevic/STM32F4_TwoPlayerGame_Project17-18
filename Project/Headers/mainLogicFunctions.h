#ifndef __MAINLOGICFUNCTIONS_H
#define __MAINLOGICFUNCTIONS_H

#include <stdlib.h>
#include "wirelessSerialCommunication.h"

#define TICK_RATE 5000000
#define initialHealth 15

void Delay(__IO uint32_t nTime);
void StartGame(void);
void BulletCycle(Queue *queue, Position plyer, Position opponent, int *playerPoints);
void TankCycle(Position *player1, Position *player2, Queue *queue1, Queue *queue2);
void TankCycle(int random1, WifiPackage *package1, WifiPackage package2, Position *player1, Position *player2, Queue *queue1, Queue *queue2);
void ReadFireButton(void);
void ReadESP(void);
void WriteESP(void);
void CheckHit(void);
void CheckEndGameCondition(int *gameRunning, int points1, int points2);
void EndGame(int winner);

#endif

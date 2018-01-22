#include "lcdfunctions.h"
#include "main.h"


#define r 15			/* velicina tenka */
#define a 10
#define rb 3 			/* velicina metka */

#define	xstart1 120   /* pocetne pozicije prvog igraca */
#define ystart1 50
#define xstart2 120		/* pocetne pozicije drugog igraca */
#define ystart2	300

#define	xScreenStart 25   
#define yScreenStart 50
#define xScreenEnd 215		
#define yScreenEnd	295

#define xt 10	/* za koliko se mijenja pozicija tenka */
#define yt 10
#define xb 20	/* za koliko se mijenja pozicija metka */
#define yb 20   

void StartScreen(void){         
	LCD_Init();
	LCD_LayerInit();
	LTDC_Cmd(ENABLE);
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
  LCD_Clear(LCD_COLOR_WHITE);
  LCD_SetFont(&Font16x24);
  LCD_SetTextColor(LCD_COLOR_BLACK); 
  LCD_DisplayStringLine(LINE(3), (uint8_t*)"   For start     ");
	LCD_DisplayStringLine(LINE(5), (uint8_t*)"     press    ");
	LCD_DisplayStringLine(LINE(7), (uint8_t*)"     button     ");
	
}

void ClearScreen (void) {
	LCD_Clear(LCD_COLOR_WHITE);
}

void Write(char *p, int n){
	LCD_SetFont(&Font16x24);
  LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_DisplayStringLine(LINE(n), (uint8_t*)p);	
}

void EndScreen(int pobjednik){					
	LCD_Clear(LCD_COLOR_WHITE);															
	LCD_SetFont(&Font16x24);
	LCD_SetTextColor(LCD_COLOR_BLACK); 
	LCD_DisplayStringLine(LINE(3), (uint8_t*)"   Winner is     ");
	LCD_DisplayStringLine(LINE(5), (uint8_t*)"     player    ");
	if(pobjednik==1) LCD_DisplayStringLine(LINE(7), (uint8_t*)"       1   ");
	else LCD_DisplayStringLine(LINE(7), (uint8_t*)"       2   ");
}

Position TankInit(int choosePlayer){					
	Position player;
					
	if(choosePlayer == 0){
		LCD_SetTextColor(LCD_COLOR_BLUE);
		player.positionX = xstart1;
		player.positionY = ystart1;
		player.direction = UP;
		LCD_FillTriangle(player.positionX+a/2, player.positionX-a/2, player.positionX, player.positionY+r, player.positionY+r, player.positionY+r+a);
	}
	else{
		LCD_SetTextColor(LCD_COLOR_RED);				
		player.positionX = xstart2;
		player.positionY = ystart2;
		player.direction = DOWN;
		LCD_FillTriangle(player.positionX-a/2, player.positionX+a/2, player.positionX, player.positionY-r, player.positionY-r, player.positionY-r-a);
	}
	
	LCD_DrawFullCircle(player.positionX, player.positionY, r);
	
	return player;
}

BulletPosition BulletInit(Position player){				
	LCD_SetTextColor(LCD_COLOR_BLACK);					
	
	BulletPosition bullet;
	
	if (player.direction==UP){
		player.positionY = player.positionY+a+r+rb;
	}
	else if (player.direction==RIGHT){
		player.positionX = player.positionX-r-a-rb;
	}
	else if (player.direction==DOWN){
		player.positionY = player.positionY-r-a-rb;
	}
	else{
		player.positionX = player.positionX+r+a+rb;
	}

	if(player.positionX > xScreenStart && player.positionX < xScreenEnd && player.positionY > yScreenStart && player.positionY < yScreenEnd){
		LCD_DrawFullCircle(player.positionX, player.positionY, rb);
		bullet.position.positionX = player.positionX;
		bullet.position.positionY = player.positionY;
		bullet.position.direction = player.direction;
		bullet.life = 10;
		
		return bullet;
	}
	
	bullet.life = 0;
	
	return bullet;
}

void BulletMove(BulletPosition *bullet){			
	BulletRemove(*bullet);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	
	if(bullet->position.direction==UP){
		if(bullet->position.positionY+yb < yScreenEnd){							
			bullet->position.positionY +=yb;																																					
		}
		else
			BulletRemove(*bullet);
	}
	else if(bullet->position.direction==RIGHT){
		if(bullet->position.positionX-xb > xScreenStart){
			bullet->position.positionX -=xb;
		}
		else
			BulletRemove(*bullet);
	}
	else if(bullet->position.direction==DOWN){
		if(bullet->position.positionY-yb > yScreenStart){
			bullet->position.positionY -=yb;
		}
		else
			BulletRemove(*bullet);
	}
	else if(bullet->position.direction==LEFT){
		if(bullet->position.positionX+xb < xScreenEnd){
			bullet->position.positionX +=xb;										
		}
		else
			BulletRemove(*bullet);
	}
	
	LCD_DrawFullCircle(bullet->position.positionX, bullet->position.positionY, rb);
}

void BulletRemove(BulletPosition bullet){
	if(bullet.position.positionX > 5 && bullet.position.positionY > 5){
		LCD_SetTextColor(LCD_COLOR_WHITE);		
		LCD_DrawFullCircle(bullet.position.positionX, bullet.position.positionY, rb+2);
	}
}

void TankMove(Position *player, Position *player2, int choosePlayer){
	TankRemove(*player);
	if(choosePlayer == 0)
		LCD_SetTextColor(LCD_COLOR_BLUE);
	else
		LCD_SetTextColor(LCD_COLOR_RED);
	
	if(player->direction==UP){							
		if(player->positionY+yt <= yScreenEnd && player->positionY+yt >= yScreenStart && abs(player->positionY - player2->positionY) > 2*(a+r))	
			player->positionY=player->positionY+yt;
		
		LCD_DrawFullCircle(player->positionX, player->positionY, r);
		LCD_FillTriangle(player->positionX+a/2, player->positionX-a/2, player->positionX, player->positionY+r, player->positionY+r, player->positionY+r+a);
	}
	else if(player->direction==RIGHT){
		if(player->positionX-xt <= xScreenEnd && player->positionX-xt >= xScreenStart && abs(player->positionX - player2->positionX) > 2*(a+r))
			player->positionX=player->positionX-xt;
		
		LCD_DrawFullCircle(player->positionX, player->positionY, r);
		LCD_FillTriangle(player->positionX-r, player->positionX-r, player->positionX-r-a, player->positionY+a/2, player->positionY-a/2, player->positionY);
	}
	else if(player->direction==DOWN){
		if(player->positionY-yt <= yScreenEnd && player->positionY-yt >= yScreenStart && abs(player->positionY - player2->positionY) > 2*(a+r))
			player->positionY=player->positionY-yt;
		
		LCD_DrawFullCircle(player->positionX, player->positionY, r);
		LCD_FillTriangle(player->positionX-a/2, player->positionX+a/2, player->positionX, player->positionY-r, player->positionY-r, player->positionY-r-a);
	}
	else if(player->direction==LEFT){
		if(player->positionX+xt <= xScreenEnd && player->positionX+xt >= xScreenStart && abs(player->positionX - player2->positionX) > 2*(a+r))
			player->positionX=player->positionX+xt;
		
		LCD_DrawFullCircle(player->positionX, player->positionY, r);
		LCD_FillTriangle(player->positionX+r, player->positionX+r, player->positionX+r+a, player->positionY-a/2, player->positionY+a/2, player->positionY);
	}
}

void TankRemove(Position player){			
	LCD_SetTextColor(LCD_COLOR_WHITE);		
	if(player.direction==UP){
		LCD_DrawFullRect(player.positionX-r, player.positionY-r, 2*r+1, 2*r+a+1);
	}
	else if(player.direction==RIGHT){
		LCD_DrawFullRect(player.positionX-r-a, player.positionY-r, 2*r+a+1, 2*r+1);
	}
	else if(player.direction==DOWN){
		LCD_DrawFullRect(player.positionX-r, player.positionY-r-a, 2*r+1, a+ 2*r+1);
	}
	else{
		LCD_DrawFullRect(player.positionX-r, player.positionY-r, 2*r+a+1, 2*r+1);
	}
}

void TankRotate(Position *player, int next, int choosePlayer){
	TankRemove(*player);
	if(choosePlayer == 0)
		LCD_SetTextColor(LCD_COLOR_BLUE);
	else
		LCD_SetTextColor(LCD_COLOR_RED);
	
	if(player->direction==UP){
		if(next==0){
			LCD_DrawFullCircle(player->positionX, player->positionY, r);
			LCD_FillTriangle(player->positionX+r, player->positionX+r, player->positionX+r+a, player->positionY-a/2, player->positionY+a/2, player->positionY);
		}
		else if(next==1){
			LCD_DrawFullCircle(player->positionX, player->positionY, r);
			LCD_FillTriangle(player->positionX-r, player->positionX-r, player->positionX-r-a, player->positionY+a/2, player->positionY-a/2, player->positionY);   
		}
	}
	else if(player->direction==RIGHT){
		if(next==0){
			LCD_DrawFullCircle(player->positionX, player->positionY, r);
			LCD_FillTriangle(player->positionX+a/2, player->positionX-a/2, player->positionX, player->positionY+r, player->positionY+r, player->positionY+r+a);
		}
		else if(next==1){
			LCD_DrawFullCircle(player->positionX, player->positionY, r);
			LCD_FillTriangle(player->positionX-a/2, player->positionX+a/2, player->positionX, player->positionY-r, player->positionY-r, player->positionY-r-a);
		}
	}
	else if(player->direction==DOWN){
		if(next==0){
			LCD_DrawFullCircle(player->positionX, player->positionY, r);
			LCD_FillTriangle(player->positionX-r, player->positionX-r, player->positionX-r-a, player->positionY+a/2, player->positionY-a/2, player->positionY);
		}
		else if(next==1){
			LCD_DrawFullCircle(player->positionX, player->positionY, r);
			LCD_FillTriangle(player->positionX+r, player->positionX+r, player->positionX+r+a, player->positionY-a/2, player->positionY+a/2, player->positionY);
		}
	}
	else{
		if(next==0){
			LCD_DrawFullCircle(player->positionX, player->positionY, r);
			LCD_FillTriangle(player->positionX-a/2, player->positionX+a/2, player->positionX, player->positionY-r, player->positionY-r, player->positionY-r-a);
		}
		else if(next==1){
			LCD_DrawFullCircle(player->positionX, player->positionY, r);
			LCD_FillTriangle(player->positionX+a/2, player->positionX-a/2, player->positionX, player->positionY+r, player->positionY+r, player->positionY+r+a);
		}
	}
	
	player->direction+= next == 0 ? (player->direction==1 ? 3 : -1) : (player->direction==4 ? -3 : 1);
}

void score(char p1, char p2){						
	char buffer[10];											
	LCD_SetFont(&Font12x12);
	LCD_ClearLine(LINE(1));
  LCD_SetTextColor(LCD_COLOR_BLACK);
	sprintf(buffer, "P1:%d P2:%d", p1, p2);
  LCD_DisplayStringLine(LINE(1), (uint8_t*)buffer);
}

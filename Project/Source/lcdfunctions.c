#include "main.h"

#define r 15			/* velicina tenka */
#define a 10
#define rb 3 			/* velicina metka */

#define	xstart1 120   /* pocetne pozicije prvog igraca */
#define ystart1 20
#define xstart2 120		/* pocetne pozicije drugog igraca */
#define ystart2	300

#define	xScreenStart 20   /* pocetne pozicije prvog igraca */
#define yScreenStart 40
#define xScreenEnd 220		/* pocetne pozicije drugog igraca */
#define yScreenEnd	300

#define xt 10	/* za koliko se mijenja pozicija tenka */
#define yt 10
#define xb 15	/* za koliko se mijenja pozicija metka */
#define yb 15   

void StartScreen(void){         /* pocetni ekran */
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

void EndScreen(int pobjednik){					/* ekran na kraju */
	LCD_Clear(LCD_COLOR_WHITE);															
	LCD_SetFont(&Font16x24);
	LCD_SetTextColor(LCD_COLOR_BLACK); 
	LCD_DisplayStringLine(LINE(3), (uint8_t*)"   Winner is     ");
	LCD_DisplayStringLine(LINE(5), (uint8_t*)"     player    ");
	if(pobjednik==1) LCD_DisplayStringLine(LINE(7), (uint8_t*)"       1   ");
	else LCD_DisplayStringLine(LINE(7), (uint8_t*)"       2   ");
}

PlayerPosition TankInit(int choosePlayer){					/* pocetna pozicija prvog igraca */
	PlayerPosition player1;
					
	if(choosePlayer == 0){
		LCD_SetTextColor(LCD_COLOR_BLUE);
		player1.positionX = xstart1;
		player1.positionY = ystart1;
		player1.direction = 1;
		LCD_FillTriangle(player1.positionX+a/2,player1.positionX-a/2,player1.positionX,player1.positionY+r,player1.positionY+r,player1.positionY+r+a);
	}
	else{
		LCD_SetTextColor(LCD_COLOR_RED);				/* x=120 , y=20 , smjer=1(prema dolje) */
		player1.positionX = xstart2;
		player1.positionY = ystart2;
		player1.direction = 3;
		LCD_FillTriangle(player1.positionX-a/2,player1.positionX+a/2,player1.positionX,player1.positionY-r,player1.positionY-r,player1.positionY-r-a);
	}
	
	LCD_DrawFullCircle(player1.positionX, player1.positionY, r);
	
	return player1;
}

BulletPosition BulletInit(PlayerPosition player){				/* pocetna pozicija metka prvog igraca */
	LCD_SetTextColor(LCD_COLOR_BLACK);					/* prima: x i y poziciju tenka i smjer prema kojem je okrenut */
	
	BulletPosition bullet;
	int x,y;
	
	x=player.positionX;
	y=player.positionY;
	
	if (player.direction==1){
		y = y+a+r+rb>0 ? y+a+r+rb : y;
	}
	else if (player.direction==2){
		x = x-r-a-rb>0 ? x-r-a-rb : x;
	}
	else if (player.direction==3){
		y = y-r-a-rb>0 ? y-r-a-rb : y;
	}
	else{
		x = x+r+a+rb>0 ? x+r+a+rb : x;
	}

	LCD_DrawFullCircle(x, y, rb);
	
	bullet.positionX = x;
	bullet.positionY = y;
	bullet.direction = player.direction;
	bullet.life = 5;
	
	return bullet;
}

void BulletMove(BulletPosition *bullet){			/* pomicanje metka */			/* prima  poziciju metka */
	int x = bullet->positionX,y = bullet->positionY;
	
	BulletRemove(*bullet);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	
	if(bullet->direction==1){							/* smjer 1=dolje, 2=lijevo, 3=gore, 4=desno */
		y+=yb;																																					
	}
	else if(bullet->direction==2 && x-xb > 0){
		x-=xb;
	}
	else if(bullet->direction==3 && y-yb > 0){
		y-=yb;
	}
	else{
		x+=xb;										
	}
	
	LCD_DrawFullCircle(x, y, rb);
	
	bullet->positionX = x;
	bullet->positionY = y;
}

void BulletRemove(BulletPosition bullet){					/* brise metak */
	LCD_SetTextColor(LCD_COLOR_WHITE);		/* prima  poziciju metka */
	LCD_DrawFullCircle(bullet.positionX, bullet.positionY, rb+2);
}

void TankMove(PlayerPosition *player1, int choosePlayer){			/* pomicanje tenka prvog igraca */
	int x,y;														/* prima  poziciju (srediste kruga) tenka i smjer prema kojem je okrenut */
	x = player1->positionX;
	y = player1->positionY;
	
	TankRemove(*player1);
	if(choosePlayer == 0)
		LCD_SetTextColor(LCD_COLOR_BLUE);
	else
		LCD_SetTextColor(LCD_COLOR_RED);
	
	if(player1->direction==1){							/* smjer 1=dolje, 2=lijevo, 3=gore, 4=desno */
		if(player1->positionY+yt <= yScreenEnd && player1->positionY+yt >= yScreenStart)	
			y=player1->positionY+yt;																																		
		LCD_DrawFullCircle(x, y, r);
		LCD_FillTriangle(x+a/2,x-a/2,x,y+r,y+r,y+r+a);
	}
	else if(player1->direction==2){
		if(player1->positionX-xt <= xScreenEnd && player1->positionX-xt >= xScreenStart)
			x=player1->positionX-xt;	
		LCD_DrawFullCircle(x, y, r);
		LCD_FillTriangle(x-r,x-r,x-r-a,y+a/2,y-a/2,y);
	}
	else if(player1->direction==3){
		if(player1->positionY-yt <= yScreenEnd && player1->positionY-yt >= yScreenStart)
			y=player1->positionY-yt;
		LCD_DrawFullCircle(x, y, r);
		LCD_FillTriangle(x-a/2,x+a/2,x,y-r,y-r,y-r-a);
	}
	else{
		if(player1->positionX+xt <= xScreenEnd && player1->positionX+xt >= xScreenStart)
			x=player1->positionX+xt;	
		LCD_DrawFullCircle(x, y, r);
		LCD_FillTriangle(x+r,x+r,x+r+a,y-a/2,y+a/2,y);
	}
	
	player1->positionX = x;
	player1->positionY = y;
}

void TankRemove(PlayerPosition player){			/* brisanje tenka */
	LCD_SetTextColor(LCD_COLOR_WHITE);		/* prima poziciju tenka */
	int x,y;
	x=player.positionX;	
	y=player.positionY;
	if(player.direction==1){
		LCD_DrawFullCircle(x, y, r);
		LCD_FillTriangle(x+a/2,x-a/2,x,y+r,y+r,y+r+a);
	}
	else if(player.direction==2){
		LCD_DrawFullCircle(x, y, r);
		LCD_FillTriangle(x-r,x-r,x-r-a,y+a/2,y-a/2,y);
	}
	else if(player.direction==3){
		LCD_DrawFullCircle(x, y, r);
		LCD_FillTriangle(x-a/2,x+a/2,x,y-r,y-r,y-r-a);
	}
	else{
		LCD_DrawFullCircle(x, y, r);
		LCD_FillTriangle(x+r,x+r,x+r+a,y-a/2,y+a/2,y);
	}
}

void TankRotate(PlayerPosition *player1, int next, int choosePlayer){    /* rotacija tenkova */
	int x,y;
	
	x=player1->positionX;	
	y=player1->positionY;
	
	TankRemove(*player1);
	if(choosePlayer == 0)
		LCD_SetTextColor(LCD_COLOR_BLUE);
	else
		LCD_SetTextColor(LCD_COLOR_RED);
	
	if(player1->direction==1){
		if(next==0){
			LCD_DrawFullCircle(x, y, r);
			LCD_FillTriangle(x+r,x+r,x+r+a,y-a/2,y+a/2,y);
		}
		else{
			LCD_DrawFullCircle(x, y, r);
			LCD_FillTriangle(x-r,x-r,x-r-a,y+a/2,y-a/2,y);   /* npr. smjer=2, next=0 => rotira u 1; next=1 =>rotira u 3 */
		}
	}
	else if(player1->direction==2){
		if(next==0){
			LCD_DrawFullCircle(x, y, r);
			LCD_FillTriangle(x+a/2,x-a/2,x,y+r,y+r,y+r+a);
		}
		else{
			LCD_DrawFullCircle(x, y, r);
			LCD_FillTriangle(x-a/2,x+a/2,x,y-r,y-r,y-r-a);
		}
	}
	else if(player1->direction==3){
		if(next==0){
			LCD_DrawFullCircle(x, y, r);
			LCD_FillTriangle(x-r,x-r,x-r-a,y+a/2,y-a/2,y);
		}
		else{
			LCD_DrawFullCircle(x, y, r);
			LCD_FillTriangle(x+r,x+r,x+r+a,y-a/2,y+a/2,y);
		}
	}
	else{
		if(next==0){
			LCD_DrawFullCircle(x, y, r);
			LCD_FillTriangle(x-a/2,x+a/2,x,y-r,y-r,y-r-a);
		}
		else{
			LCD_DrawFullCircle(x, y, r);
			LCD_FillTriangle(x+a/2,x-a/2,x,y+r,y+r,y+r+a);
		}
	}
	
	player1->direction+= next == 0 ? (player1->direction==1 ? 3 : -1) : (player1->direction==4 ? -3 : 1);
}

void score(char p1, char p2){						/* prikaz rezultata */
	char buffer[10];											/* prima rezultat */
	LCD_SetFont(&Font12x12);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_ClearLine(LINE(1));
	LCD_ClearLine(LINE(2));
  LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_DisplayStringLine(LINE(1), (uint8_t*)"P1:  P2: ");
	sprintf(buffer, " %d   %d", p1, p2);
  LCD_DisplayStringLine(LINE(2), (uint8_t*)buffer);
}

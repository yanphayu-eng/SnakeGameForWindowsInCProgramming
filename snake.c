#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "yuC.h"

int main(){

	system("cls");
	hideCursor();
	int w,h;
	getWH(&w,&h);

	short x = w/2;
	short y = h/2;
	short ch;
	short oldX = x;
	short oldY = y;
	short dx = 0;
	short dy = 0;
	short fx = w/4;
	short fy = h/6;
	short tx[1000];
	short ty[1000];
	short tl = 0;
	short speed = 100;
	int sw = w;
	int sh = h;

	snakeMap(w,h);

	srand(time(NULL));

	gotoxy(x,y);
	printf(RED1"■"RESET);

	gotoxy(fx,fy);
	printf(LIGHTGREEN6"■"RESET);

	while(1){
		int ew,eh;
		getWH(&ew,&eh);
		if(sw != ew && sh != eh){
			system("cls");
			showCursor();
			return 0;
		}
		oldX = x;
		oldY = y;
		if(kbhit()){
			ch = getch();
			if(ch == 0 || ch == 224) ch = getch();

			switch(ch){
				case 72: if(dy != 1){dx = 0; dy =-1;} break;
				case 80: if(dy !=-1){dx = 0; dy = 1;} break;
				case 75: if(dx != 1){dx =-1; dy = 0;} break;
				case 77: if(dx !=-1){dx = 1; dy = 0;} break;
			}
		}

		if(tl > 0){
			gotoxy(tx[tl - 1],ty[tl - 1]);
			printf(" ");
		}

		for(int i = tl; i > 0; i--){
			tx[i] = tx[i-1];
			ty[i] = ty[i-1];
		}

		for(int i = 0; i < tl; i++){
			if(x == tx[i] && y == ty[i]){
				showCursor();
				gameOver();
				gotoxy(1,h-2);
				getchar();
				gotoxy(1,h-1);
				return 0;
			}
		}

		if(x == 0 || x == w-1 || y == 0 || y == h-1){
			showCursor();
			gameOver();
			gotoxy(1,h-2);
			getchar();
			gotoxy(1,h-1);
			return 0;
		}
		
		tx[0] = x;
		ty[0] = y;
		x += dx;
		y += dy;

		if(fx == x && fy == y){
			tl++;
			if(speed > 50) speed -= 5;
			fx = (rand() % (w-2)) + 1;
			fy = (rand() % (h-2)) + 1;
			gotoxy(fx,fy);
			printf(LIGHTGREEN6"■"RESET);
		}

		gotoxy(oldX,oldY);
		printf(" ");
		gotoxy(x,y);
		printf(RED1"■"RESET);

		for(int i = 0; i < tl; i++)
		{
			gotoxy(tx[i],ty[i]);
			printf(GREEN1"■"RESET);
		}

		Sleep(speed);
	}

}
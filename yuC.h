#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define RED1 "\033[38;2;237;23;23m"
#define RED2 "\033[38;2;242;50;17m"
#define RED3 "\033[38;2;246;70;12m"
#define RED4 "\033[38;2;247;95;6m"
#define RED5 "\033[38;2;250;119;0m"
#define RED6 "\033[38;2;250;125;0m"

#define LIGHTGREEN1 "\033[38;2;175;255;0m"
#define LIGHTGREEN2 "\033[38;2;175;255;95m"
#define LIGHTGREEN3 "\033[38;2;175;255;135m"
#define LIGHTGREEN4 "\033[38;2;175;255;175m"
#define LIGHTGREEN5 "\033[38;2;175;255;200m"
#define LIGHTGREEN6 "\033[38;2;175;255;215m"

#define BLUE1 "\033[38;2;0;37;246m"
#define BLUE2 "\033[38;2;0;74;248m"
#define BLUE3 "\033[38;2;0;111;249m"
#define BLUE4 "\033[38;2;0;148;251m"
#define BLUE5 "\033[38;2;0;185;252m"
#define BLUE6 "\033[38;2;0;185;253m"

#define GREEN1 "\033[38;2;0;255;0m"
#define GREEN2 "\033[38;2;0;255;50m"
#define GREEN3 "\033[38;2;0;255;95m"
#define GREEN4 "\033[38;2;0;255;135m"
#define GREEN5 "\033[38;2;0;255;175m"
#define GREEN6 "\033[38;2;0;255;200m"

#define PINK1 "\033[38;2;198;50;100m"
#define PINK2 "\033[38;2;212;76;135m"
#define PINK3 "\033[38;2;227;102;177m"
#define PINK4 "\033[38;2;241;127;197m"
#define PINK5 "\033[38;2;255;153;218m"
#define PINK6 "\033[38;2;255;153;220m"

#define RESET "\033[0m"

void gotoxy(int x,int y){
    COORD c = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void hideCursor(){
	CONSOLE_CURSOR_INFO c;
	c.dwSize = 1;
	c.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c);
}

void showCursor(){
	CONSOLE_CURSOR_INFO c;
	c.dwSize = 1;
	c.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c);
}

void enableANSI(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}


void getWH(int *w,int *h){
	CONSOLE_SCREEN_BUFFER_INFO c;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c);
	*w = c.srWindow.Right - c.srWindow.Left + 1;
	*h = c.srWindow.Bottom - c.srWindow.Top + 1;
}

// void gameOver(){
//     system("chcp 65001 > nul");
//     int w, h;
//     getWH(&w, &h);

//     const char *gameOverText[] = {
//         "  ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ ",
//         " ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗",
//         " ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝",
//         " ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗",
//         " ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║",
//         "  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝"
//     };

//     int asciiWidth  = 78;   // adjust if needed
//     int asciiHeight = 6;

//     int startX = (w - asciiWidth) / 2;
//     int startY = (h - asciiHeight) / 2;

//     for(int i = 0; i < asciiHeight; i++){
//         gotoxy(startX, startY + i);
//         printf("%s", gameOverText[i]);
//     }
// }
void gameOver(){
    system("chcp 65001 > nul");
    enableANSI();
    int w, h;
    getWH(&w, &h);

    const char *title[] = {
        "  _____                 ____              ",
        " / ___/__ ___ _  ___   / __ \\_  _____ ____",
        "/ (_ / _ `/  ' \\/ -_) / /_/ / |/ / -_) __/",
        "\\___/\\_,_/_/_/_/\\__/  \\____/|___/\\__/_/  "
    };

    int lines = sizeof(title) / sizeof(title[0]);

    int asciiWidth = 0;
    for(int i = 0; i < lines; i++){
        int len = strlen(title[i]);
        if(len > asciiWidth) asciiWidth = len;
    }

    int startX = (w - asciiWidth) / 2;
    int startY = (h - lines) / 2;

    for(int i = 0; i < lines; i++){
        gotoxy(startX, startY + i);
        printf(RED1 "%s" RESET, title[i]);
    }

}

void snakeMap(int width,int height){
	system("chcp 65001 > nul");
	for(int row = 0; row < height; row++){
		for(int col = 0; col < width; col++){
			if(row == 0 || row == height-1 || col == 0 || col == width-1){
				if(row == 0 && col == 0){
					gotoxy(col,row);
					printf("╔");
				}
				else if(row == 0 && col == width-1){
					gotoxy(col,row);
					printf("╗");
				}
				else if(row == height-1 && col == 0){
					gotoxy(col,row);
					printf("╚");
				}
				else if(row == height-1 && col == width-1){
					gotoxy(col,row);
					printf("╝");
				}
				else if(row == 0 || row == height-1){
					gotoxy(col,row);
					printf("═");
				}
				else{
					gotoxy(col,row);
					printf("║");
				}
			}
			else{
				gotoxy(col,row);
				printf(" ");
			}
		}
	}
}

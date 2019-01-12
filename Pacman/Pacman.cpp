
#include "pch.h"
#include <iostream>
#include <string>
#include <time.h>
#include <conio.h>

using namespace std;

#define WALL "■"
#define COIN "○"
#define PACMAN "●"
#define GHOST "◆"
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ARROW 224

string map[20][20];
int pacmanX = 1;
int pacmanY = 1;
int ghostX[8] = {17,};
int ghostY[8] = {8};
int plusvalue = 1;
void PrintMap()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			cout << map[i][j];
		}
		printf("\n");
	}
}
void 가로벽넣기(int 시작행,int 시작열, int 개수)
{
	for (int i = 시작열; i < 시작열 + 개수; i++)
	{
		map[시작행][i] = WALL;
	}
 }

void 세로벽넣기(int 시작열, int 시작행,  int 개수)
{
	for (int i = 시작행; i < 시작행+개수;i++)
	{
		map[i][시작열] = WALL;
	}
}

void 초기화()
{



	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = "  ";
		}
	}

	for (int i = 0; i < 20; i++)
	{
		map[i][0] = WALL;
		map[0][i] = WALL;
		map[i][19] = WALL;
		map[19][i] = WALL;


	}

	가로벽넣기(1, 2, 5);
	가로벽넣기(1, 13, 5);
	가로벽넣기(3, 2, 5);
	가로벽넣기(3, 13, 5);
	가로벽넣기(9, 2, 4);
	가로벽넣기(10, 2, 4);
	가로벽넣기(9, 14, 4);
	가로벽넣기(10, 14, 4);
	가로벽넣기(8, 7, 6);
	가로벽넣기(11, 7, 2);
	가로벽넣기(11, 10, 3);
	가로벽넣기(16, 2, 5);
	가로벽넣기(16, 13, 5);
	가로벽넣기(18, 2, 5);
	가로벽넣기(18, 13, 5);

	세로벽넣기(6, 4, 4);
	세로벽넣기(13, 4, 4);
	세로벽넣기(7, 9, 2);
	세로벽넣기(12, 9, 2);
	세로벽넣기(6, 12, 4);
	세로벽넣기(13, 12, 4);

	for (int i = 0; i < 30; i++)
	{

		int 행 = rand() % 20;
		int 열 = rand() % 20;

		if (map[행][열] == COIN || map[행][열] == WALL)
		{
			i--;
			continue;
		}

		map[행][열] = COIN;
	}

	map[pacmanX][pacmanY] = PACMAN;

	for (int i = 0; i < 8; i++)
	{
		map[ghostX[i]][ghostY[i]] = GHOST; //8~11이동
	}
}
void 플레이어키보드입력()
{
	if (kbhit() == 1)
	{
		int key = getch();
		if (key == ARROW)
		{
			key = getch();
			if (key == RIGHT)
			{
				if (map[pacmanX][pacmanY + 1] != WALL)
				{
					pacmanY += 1;
					map[pacmanX][pacmanY] = PACMAN;
					map[pacmanX][pacmanY - 1] = "  ";
				}
			}
			if (key == DOWN)
			{
				if (map[pacmanX + 1][pacmanY] != WALL)
				{
					pacmanX += 1;
					map[pacmanX][pacmanY] = PACMAN;
					map[pacmanX - 1][pacmanY] = "  ";
				}
			}
			if (key == UP)
			{
				if (map[pacmanX - 1][pacmanY] != WALL)
				{
					pacmanX -= 1;
					map[pacmanX][pacmanY] = PACMAN;
					map[pacmanX + 1][pacmanY] = "  ";
				}


			}
			if (key == LEFT)
			{
				//안움직일때 - 움직일려는 칸이 벽이면
				//////////////////////////////////////////
				//움직일떄 - 움직일려는 칸이 벽이 아니면
				if (map[pacmanX][pacmanY - 1] != WALL)
				{
					pacmanY -= 1;
					map[pacmanX][pacmanY] = PACMAN;
					map[pacmanX][pacmanY + 1] = "  ";
				}
			}

		}
	}
}

void 고스트이동()
{

		

}

void 게임루프()
{

	while (true)//게임 반복문
	{
		고스트이동();
		플레이어키보드입력();
		PrintMap();
		system("cls");

	}

}



int main()
{

	srand(time(NULL));
 
	초기화();

	
	게임루프();
	

	
}


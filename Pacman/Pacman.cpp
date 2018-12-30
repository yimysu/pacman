
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
#define LEFT 
string map[20][20];
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
	map[1][1] = PACMAN;
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

}



int main()
{

	srand(time(NULL));
 
	초기화();
	while (true)
	{
		
		if (kbhit() == 1)
		{
			cout << getch() << endl;
		}

		
		
	}
	
	PrintMap();
	
}


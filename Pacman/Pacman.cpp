
#include "pch.h"

using namespace std;

#define WALL "■"
#define COIN "＊"
#define PACMAN "●"
#define GHOST "◆"
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ARROW 224
#define GHOST_COUNT 4
#define BLANK "  "

string map[20][20];
int pacmanX = 1;
int pacmanY = 1;
int 가로고스트X[GHOST_COUNT] = {17,9,10,2};
int 가로고스트Y[GHOST_COUNT] = {8,1,14,18};
int 가로고스트plusValue[GHOST_COUNT] = { 1,1,1,1 };


int 세로고스트X[GHOST_COUNT] = { 1,1,1,9 };
int 세로고스트Y[GHOST_COUNT] = {18,9,9,1  };
int 세로고스트plusValue[GHOST_COUNT] = { 1,1,1,1 };

int coinCount = 0;

void PrintMap()
{
	string buffer;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			buffer += map[i][j];

		}
		buffer += "\n";
	}

	buffer += "\n코인갯수 : ";
	buffer += to_string(coinCount);
	BufferWrite(0, 0, buffer.c_str());
	Flipping();
	
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
	CreateBuffer();


	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = COIN;
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
	//가로벽넣기(9, 2, 4);
	//가로벽넣기(10, 2, 4);
	//가로벽넣기(9, 14, 4);
	//가로벽넣기(10, 14, 4);
	//가로벽넣기(8, 7, 6);
	//가로벽넣기(11, 7, 2);
	//가로벽넣기(11, 10, 3);
	가로벽넣기(16, 2, 5);
	가로벽넣기(16, 13, 5);
	가로벽넣기(18, 2, 5);
	가로벽넣기(18, 13, 5);

	세로벽넣기(6, 4, 4);
	세로벽넣기(13, 4, 4);
	//세로벽넣기(7, 9, 2);
	//세로벽넣기(12, 9, 2);
	세로벽넣기(6, 12, 4);
	세로벽넣기(13, 12, 4);

	//for (int i = 0; i < 40; i++)
	//{

	//	int 행 = rand() % 20;
	//	int 열 = rand() % 20;

	//	if (map[행][열] == COIN || map[행][열] == WALL)
	//	{
	//		i--;
	//		continue;
	//	}

	//	map[행][열] = COIN;
	//}

	map[pacmanX][pacmanY] = PACMAN;

	for (int i = 0; i < 8; i++)
	{
		map[가로고스트X[i]][가로고스트Y[i]] = GHOST; //8~11이동
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
					if (map[pacmanX][pacmanY] == COIN)
					{
						coinCount += 1;
					}
					map[pacmanX][pacmanY] = PACMAN;
					map[pacmanX][pacmanY - 1] = BLANK;
				}
			}
			if (key == DOWN)
			{
				if (map[pacmanX + 1][pacmanY] != WALL)
				{
					pacmanX += 1;
					if (map[pacmanX][pacmanY] == COIN)
					{
						coinCount += 1;
					}
					map[pacmanX][pacmanY] = PACMAN;
					map[pacmanX - 1][pacmanY] = BLANK;
				}
			}
			if (key == UP)
			{
				if (map[pacmanX - 1][pacmanY] != WALL)
				{
					pacmanX -= 1;
					if (map[pacmanX][pacmanY] == COIN)
					{
						coinCount += 1;
					}
					map[pacmanX][pacmanY] = PACMAN;
					map[pacmanX + 1][pacmanY] = BLANK;
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
					if (map[pacmanX][pacmanY] == COIN)
					{
						coinCount += 1;
					}
					map[pacmanX][pacmanY] = PACMAN;
					map[pacmanX][pacmanY + 1] = BLANK;
				}
			}

		}
	}
}

void 고스트이동()
{
	for (int i = 0; i < GHOST_COUNT; i++)
	{
		if (map[가로고스트X[i]][가로고스트Y[i] + 가로고스트plusValue[i]] != WALL)
		{
			가로고스트Y[i] += 가로고스트plusValue[i];
			map[가로고스트X[i]][가로고스트Y[i]] = GHOST;
			map[가로고스트X[i]][가로고스트Y[i] - 가로고스트plusValue[i]] = COIN;
		}
		else
		{
			가로고스트plusValue[i] *= -1;
		}
	}
	for (int i = 0; i < GHOST_COUNT; i++)
	{
		if (map[세로고스트X[i] + 세로고스트plusValue[i]][세로고스트Y[i]] != WALL)
		{
			세로고스트X[i] += 세로고스트plusValue[i];
			map[세로고스트X[i]][세로고스트Y[i]] = GHOST;
			map[세로고스트X[i]- 세로고스트plusValue[i]][세로고스트Y[i]] = COIN;
		}
		else
		{
			세로고스트plusValue[i] *= -1;
		}
	}
	
	

		

}

void 게임루프()
{

	while (true)//게임 반복문
	{
		고스트이동();
		플레이어키보드입력();
		PrintMap();
		Sleep(SLEEP_TIME);
	

	}

	Release();

}



int main()
{

	srand(time(NULL));
 
	초기화();

	
	게임루프();
	

	
}


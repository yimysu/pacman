
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
#define TOTAL_COIN 267

string map[20][20];

int pacmanX = 1;
int pacmanY = 1;
int pacmanHp = 5;

//int 가로고스트X[GHOST_COUNT] = {17,9,10,2};
//int 가로고스트Y[GHOST_COUNT] = {8,1,14,18};
//int 가로고스트plusValue[GHOST_COUNT] = { 1,1,1,1 };


struct Ghost
{
	int x;
	int y;
	int plusValue;
	string previousValue;
};

Ghost 가로고스트[GHOST_COUNT] = 
{
	{17,8,1,COIN},
	{9,1,1,COIN},
	{10,14,1,COIN},
	{2,18,1,COIN}
};







//int 세로고스트X[GHOST_COUNT] = { 1,1,1,9 };
//int 세로고스트Y[GHOST_COUNT] = {18,9,9,1  };
//int 세로고스트plusValue[GHOST_COUNT] = { 1,1,1,1 };

Ghost 세로고스트[GHOST_COUNT] =
{
	{1,18,1,COIN},
	{5,11,1,COIN},
	{1,8,1,COIN},
	{9,1,1,COIN}
};



int coinCount = 0;

void PrintMap()
{
	string buffer;

	string tempMap[20][20];
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			tempMap[i][j] = map[i][j];
		}
	}


	for (int i = 0; i < GHOST_COUNT; i++)
	{
		tempMap[가로고스트[i].x][가로고스트[i].y] = GHOST;
		tempMap[세로고스트[i].x][세로고스트[i].y] = GHOST;
	}



	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{

			buffer += tempMap[i][j];

		}
		buffer += "\n";
	}

	buffer += "\n코인갯수 : ";
	buffer += to_string(coinCount);
	buffer += " HP : ";
	buffer += to_string(pacmanHp/10);
	buffer += to_string(pacmanHp % 10);

	if (pacmanHp <= 0)
	{
		buffer += "\nGAME OVER";
	}
	else if (coinCount >= TOTAL_COIN)
	{
		buffer += "\nWin";
	}


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

	map[pacmanX][pacmanY] = PACMAN;
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
		if (map[가로고스트[i].x][가로고스트[i].y + 가로고스트[i].plusValue] != WALL)
		{
			가로고스트[i].y += 가로고스트[i].plusValue;
		}
		else
		{
			가로고스트[i].plusValue *= -1;
		}
	}
	for (int i = 0; i < GHOST_COUNT; i++)
	{
		if (map[세로고스트[i].x + 세로고스트[i].plusValue][세로고스트[i].y] != WALL)
		{
			세로고스트[i].x += 세로고스트[i].plusValue;
		}
		else
		{
			세로고스트[i].plusValue *= -1;
		}
	}
	
	

		

}

void 충돌처리()
{
	for (int i = 0; i < GHOST_COUNT; i++)
	{
		if (pacmanX == 가로고스트[i].x&&pacmanY == 가로고스트[i].y)
		{
			pacmanHp -= 1;
		}
		if (pacmanX == 세로고스트[i].x&&pacmanY == 세로고스트[i].y)
		{
			pacmanHp -= 1;
		}
		
	}
	
}

void 게임루프()
{

	while (true)//게임 반복문
	{
		if (pacmanHp > 0 && coinCount < TOTAL_COIN)
		{
			고스트이동();
			플레이어키보드입력();
			충돌처리();
		}
		
		PrintMap();
		Sleep(SLEEP_TIME);
	

	}


	

	Release();

}



int main()
{

	srand(time(NULL));
	int select;
	printf("난이도를 선택하세요 1.최상 2.상 3.중 4.하 5.최하 : ");
	scanf("%d", &select);
 
	switch (select)
	{
	case 1:
			pacmanHp = 2;
			break;
	case 2:
		pacmanHp = 5;
		break;
	case 3:
		pacmanHp = 10;
			break;
	case 4:
		pacmanHp = 15;
		break;
	case 5:
		pacmanHp = 99;
		break;



	}
	초기화();

	
	게임루프();
	

	
}


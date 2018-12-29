
#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

#define WALL "■"

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

int main()
{

	

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = "  ";
		}
		printf("\n");
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
	PrintMap();

}


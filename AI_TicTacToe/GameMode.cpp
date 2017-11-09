//play by pressing RightNumKeys
#define NUM_7 0,0
#define NUM_8 0,1
#define NUM_9 0,2
#define NUM_4 1,0
#define NUM_5 1,1
#define NUM_6 1,2
#define NUM_1 2,0
#define NUM_2 2,1
#define NUM_3 2,2

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include "AI_Levels.h"
using namespace std;

int Player_Turn(int **field, char input, bool show_filed = true);

void PutPlayerMark(int **field, int x, int y)
{
	if (!field[x][y])
		field[x][y] = ZERO;
	else
	{
		char input;
		cout << "WRONG INPUT, TRY AGAIN \n";
		cin >> input;
		Player_Turn(field, input, false);
	}
}

bool DrawField(int **field) //draws field to console, return "true" if there no free space on a field
{
	bool no_free_cells = true;
	int one_time = 1;
	char ch = 'h';
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
		{
			switch (field[i][j])
			{
			case CROSS:
				ch = 'X';
				break;
			case ZERO:
				ch = 'O';
				break;
			case NULL:
				ch = '_';
				if (one_time--)
					no_free_cells = false;
				break;
			default:
				cout << "ARRAY IS DAMAGED!!\n";
			}
			cout << " | " << ch << " | ";
		}
		cout << endl;
	}
	cout << endl;
	return no_free_cells;
}

int isGameEnded(int **field) //return value: NULL -game still on, CROSS - AI won, ZERO - player won
{
	int field_mark;
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
			if (field[i][j] != NULL) //CROSS is AI symbol
			{
				field_mark = field[i][j];
				//here we check all cells (around)near current
				for (int a = -1; a <= 1; ++a)
					for (int b = -1; b <= 1; ++b)
					{
						if (!a && !b) //if it`s current cell
							continue;
						//here we specify the position of sell near [i][j] cell
						int second_cell_x = i + a,
							second_cell_y = j + b;
						//next I check is cell I`m looking at out of bounds
						if (AI::isCellInbound(second_cell_x, second_cell_y))
							if (field[second_cell_x][second_cell_y] == field_mark) 
							{												 
								//if it`s true, we have too	            |x|_|_| |x|_|_|
								//check next cell in a row after them   |x|_|_| |_|X|_|
								//                                      |_|_|_| |_|_|_|	

								//first we find a offset vector
								int offset_x = second_cell_x - i,
									offset_y = second_cell_y - j;

								//check is cell after second_cell is free, if free --> put our mark there 
								if (AI::isCellInbound(second_cell_x + offset_x, second_cell_y + offset_y))
									if (field[second_cell_x + offset_x][second_cell_y + offset_y] == field_mark) //FAME WON
										return field_mark;
							}
					}
			}
	}
	return NULL;
}

int AI_Turn(AI_Lvl1 &ai, int **field)
{
	ai.MakeATurn();  
	if (isGameEnded((int**)field))
	{
		cout << "\n !!! AI WON !!! \n";
		DrawField((int**)field);
		return 1;//end
	}
	if (DrawField((int**)field))
	{
		cout << "\n !!! NO SPACE LEFT --- DRAW!!! \n";
		return 1;//end
	}
	return 0;
}

int Player_Turn(int **field, char input, bool show_field)
{
	switch (input)
	{
	case 'z':
		PutPlayerMark((int**)field, NUM_1);
		break;
	case 'x':
		PutPlayerMark((int**)field, NUM_2);
		break;
	case 'c':
		PutPlayerMark((int**)field, NUM_3);
		break;
	case 'a':
		PutPlayerMark((int**)field, NUM_4);
		break;
	case 's':
		PutPlayerMark((int**)field, NUM_5);
		break;
	case 'd':
		PutPlayerMark((int**)field, NUM_6);
		break;
	case 'q':
		PutPlayerMark((int**)field, NUM_7);
		break;
	case 'w':
		PutPlayerMark((int**)field, NUM_8);
		break;
	case 'e':
		PutPlayerMark((int**)field, NUM_9);
		break;
	default:
		cout << "WRONG INPUT\n";
		break;
	}
	if (isGameEnded((int**)field))
	{
		cout << "\n !!! PLAYER WON !!! \n";
		DrawField((int**)field);
		return 1;//end
	}
	if(show_field)
		if (DrawField((int**)field))
		{
			cout << "\n !!! NO SPACE LEFT --- DRAW!!! \n";
			return 1;//end
		}
	return 0;
}
int main()
{	
	srand(time(NULL));
	int **field = new int*[FIELD_SIDE];
	for (int i = 0; i < FIELD_SIDE; ++i)
		field[i] = new int[FIELD_SIDE];
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
		{
			field[i][j] = 0;
		}
	}

	AI_Lvl1 ai((int**)field);
	char input;
	int hows_first = rand() % 2;
	while (1)
	{
		if (hows_first)
		{
			if (AI_Turn(ai, field))
				break;
			cin >> input;
			if (Player_Turn(field, input))
				break;
		}
		else
		{
			cout << "\n YOUR TURN \n";
			DrawField((int**)field);
			cin >> input;
			if (Player_Turn(field, input))
				break;
			if (AI_Turn(ai, field))
				break;
		}

		Sleep(1000);
	}
	Sleep(20000);

}
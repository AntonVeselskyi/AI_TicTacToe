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
#include "AI_Levels.h"
using namespace std;

void PutPlayerMark(int **field, int x, int y)
{
	field[x][y] = ZERO;
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
							if (field[second_cell_x][second_cell_y] == field_mark) //if it`s true, we have too		|x|_|_|	|x|_|_|
							{												  //check next cell in a row after them	|x|_|_|	|_|X|_|
																			  //									|_|_|_|	|_|_|_|	
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

int main()
{
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
	int input;
	while (1)
	{
		ai.MakeATurn();   //TODO: AI makes mark first for now, will add randomness later
		if (isGameEnded((int**)field))
		{
			cout << "\n !!! AI WON !!! \n";
			DrawField((int**)field);
			break;
		}
		if(DrawField((int**)field))
		{
			cout << "\n !!! NO SPACE LEFT --- DRAW!!! \n";
			break;
		}

		cin >> input;
		switch (input)
		{
		case 1:
			PutPlayerMark((int**)field, NUM_1);
			break;
		case 2:
			PutPlayerMark((int**)field, NUM_2);
			break;
		case 3:
			PutPlayerMark((int**)field, NUM_3);
			break;
		case 4:
			PutPlayerMark((int**)field, NUM_4);
			break;
		case 5:
			PutPlayerMark((int**)field, NUM_5);
			break;
		case 6:
			PutPlayerMark((int**)field, NUM_6);
			break;
		case 7:
			PutPlayerMark((int**)field, NUM_7);
			break;
		case 8:
			PutPlayerMark((int**)field, NUM_8);
			break;
		case 9:
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
			break;
		}
		if (DrawField((int**)field))
		{
			cout << "\n !!! NO SPACE LEFT --- DRAW!!! \n";
			break;
		}

		Sleep(1000);
	}
	Sleep(20000);

}
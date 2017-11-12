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

#define GAME_ENDED (1)
#define GAME_CONTINUE (0)

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include "AI_Levels.h"

//declaration Player_Turn needed, because there is scenario 
//when PutPlayerMark() calls Player_Turn() and vice versa.
int Player_Turn(Field &field, char input, bool show_filed = true);

void PutPlayerMark(Field &field, int x, int y)
{
	if (AI::IsCellInbound(x,y) && field[x][y] == 0)
		field[x][y] = PLAYER_MARK;
	else
	{
		char input;
		std::cout << "WRONG INPUT, TRY AGAIN \n";
		std::cin >> input;
		Player_Turn(field, input, false);
	}
}

void ImplementPlayerInput(char input, Field &field)
{
	switch (input)
	{
	case 'z':
		PutPlayerMark(field, NUM_1);
		break;
	case 'x':
		PutPlayerMark(field, NUM_2);
		break;
	case 'c':
		PutPlayerMark(field, NUM_3);
		break;
	case 'a':
		PutPlayerMark(field, NUM_4);
		break;
	case 's':
		PutPlayerMark(field, NUM_5);
		break;
	case 'd':
		PutPlayerMark(field, NUM_6);
		break;
	case 'q':
		PutPlayerMark(field, NUM_7);
		break;
	case 'w':
		PutPlayerMark(field, NUM_8);
		break;
	case 'e':
		PutPlayerMark(field, NUM_9);
		break;
	default:
		char input;
		std::cout << "WRONG INPUT, TRY AGAIN \n";
		std::cin >> input;
		Player_Turn(field, input, false);
		break;
	}
}

bool DrawField(const Field &field) //draws field to console, return "false" if there no free space on a field
{
	bool free_cells_exist = false;
	int one_time = 1;
	char ch = 'h';
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
		{
			switch (field[i][j])
			{
			case AI_MARK:
				ch = 'X';
				break;
			case PLAYER_MARK:
				ch = 'O';
				break;
			case NULL:
				ch = '_';
				if (one_time--)
					free_cells_exist = true;
				break;
			default:
				std::cout << "ARRAY IS DAMAGED!!\n";
			}
			std::cout << " | " << ch << " | ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return free_cells_exist;
}

int IsGameEnded(const Field &field) //return value: NULL - game still on, AI_MARK - AI won, PLAYER_MARK - player won
{
	int field_mark;
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
			if (field[i][j] != NULL) //AI_MARK is AI symbol
			{
				field_mark = field[i][j];
				//here we check all cells (around)near current
				for (int iterator_x = -1; iterator_x <= 1; ++iterator_x)
					for (int iterator_y = -1; iterator_y <= 1; ++iterator_y)
					{
						if (!iterator_x && !iterator_y) //if it`s current cell
							continue;
						//here we specify the position of sell near [i][j] cell
						int second_cell_x = i + iterator_x;
						int second_cell_y = j + iterator_y;

						if (AI::IsCellInbound(second_cell_x, second_cell_y))
							if (field[second_cell_x][second_cell_y] == field_mark) 
							{												 
								//if it`s true, we have too
								//check next cell in a row after them

								//first we find a offset vector
								int offset_x = second_cell_x - i;
								int offset_y = second_cell_y - j;

								//check is cell after second_cell is free, if free --> put our mark there 
								if (AI::IsCellInbound(second_cell_x + offset_x, second_cell_y + offset_y))
									if (field[second_cell_x + offset_x][second_cell_y + offset_y] == field_mark) //FAME WON
										return field_mark;
							}
					}
			}
	}
	return NULL;
}

int AI_Turn(AI_Lvl1 &ai, Field &field)
{
	ai.MakeATurn();  
	if (IsGameEnded(field))
	{
		std::cout << "\n !!! AI WON !!! \n";
		DrawField(field);
		return GAME_ENDED;
	}
	if (!DrawField(field))
	{
		std::cout << "\n !!! NO SPACE LEFT --- DRAW!!! \n";
		return GAME_ENDED;
	}
	return GAME_CONTINUE;
}

int Player_Turn(Field &field, char input, bool show_field)
{
	ImplementPlayerInput(input, field);

	if (IsGameEnded(field))
	{
		std::cout << "\n !!! PLAYER WON !!! \n";
		DrawField(field);
		return GAME_ENDED;
	}
	if (show_field && !DrawField(field))
	{
		std::cout << "\n !!! NO SPACE LEFT --- DRAW!!! \n";
		return GAME_ENDED;
	}
	return GAME_CONTINUE;
}


int main()
{	
	srand(time(NULL));

	Field field(3, std::vector<int>(3, 0));

	AI_Lvl1 ai(field);
	char input;
	int hows_first = rand() % 2;
	while (1)
	{
		if (hows_first)
		{
			if (AI_Turn(ai, field) == GAME_ENDED)
				break;
			Sleep(1000);
			std::cin >> input;
			if (Player_Turn(field, input) == GAME_ENDED)
				break;
		}
		else
		{
			std::cout << "\n YOUR TURN \n";
			DrawField(field);
			std::cin >> input;
			if (Player_Turn(field, input) == GAME_ENDED)
				break;
			Sleep(1000);
			if (AI_Turn(ai, field) == GAME_ENDED)
				break;
		}
	}
	Sleep(10000);

	return 0;

}
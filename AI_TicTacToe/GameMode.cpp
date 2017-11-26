//play by pressing qwe asd zxc buttons
#define GAME_ENDED (1)
#define GAME_CONTINUE (0)

#include <iostream>
#include "GameMode.h"


void PrintAsciLogo()
{
	std::cout <<
		" _______ _          _______             _______         \n"
		"|__   __(_)        |__   __|           |__   __|        \n"
		"   | |   _  ___ ______| | __ _  ___ ______| | ___   ___ \n"
		"   | |  | |/ __|______| |/ _` |/ __|______| |/ _ \\ / _ \\\n"
		"   | |  | | (__       | | (_| | (__       | | (_) |  __/ \n"
		"   |_|  |_|\\___|      |_|\\__,_|\\___|      |_|\\___/ \\___| \n";
}

void PutPlayerMark(Field &field, std::pair<int,int> point)
{
	if (AI_Helper::IsCellInbound(point.first, point.second) && field[point.first][point.second] == 0)
	{
		field[point.first][point.second] = PLAYER_MARK;
	}
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
		PutPlayerMark(field, std::pair<int, int>(2, 0));
		break;
	case 'x':
		PutPlayerMark(field, std::pair<int, int>(2, 1));
		break;
	case 'c':
		PutPlayerMark(field, std::pair<int, int>(2, 2));
		break;
	case 'a':
		PutPlayerMark(field, std::pair<int, int>(1, 0));
		break;
	case 's':
		PutPlayerMark(field, std::pair<int, int>(1, 1));
		break;
	case 'd':
		PutPlayerMark(field, std::pair<int, int>(1, 2));
		break;
	case 'q':
		PutPlayerMark(field, std::pair<int, int>(0, 0));
		break;
	case 'w':
		PutPlayerMark(field, std::pair<int, int>(0, 1));
		break;
	case 'e':
		PutPlayerMark(field, std::pair<int, int>(0, 2));
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
				{
					free_cells_exist = true;
				}
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

bool IsGameEnded(const Field &field)
{
	int field_mark;
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
			if (field[i][j] != NULL) 
			{
				field_mark = field[i][j];
				//here we check all cells (around)near current
				for (int cell_near_x = -1; cell_near_x <= 1; ++cell_near_x)
					for (int cell_near_y = -1; cell_near_y <= 1; ++cell_near_y)
					{
						if (!cell_near_x && !cell_near_y) //if it`s current cell
							continue;
						//here we specify the position of sell near [i][j] cell
						int second_cell_x = i + cell_near_x;
						int second_cell_y = j + cell_near_y;

						if (AI_Helper::IsCellInbound(second_cell_x, second_cell_y) &&
							(field[second_cell_x][second_cell_y] == field_mark)) 
							{												 
								//if it`s true, we have too
								//check next cell in a row after them

								//first we find a offset vector
								int offset_x = second_cell_x - i;
								int offset_y = second_cell_y - j;

								//check is cell after second_cell is free, if free --> put our mark there 
								if (AI_Helper::IsCellInbound(second_cell_x + offset_x, second_cell_y + offset_y))
									if (field[second_cell_x + offset_x][second_cell_y + offset_y] == field_mark) //FAME WON
										return field_mark;
							}
					}
			}
	}
	return NULL;
}

int AI_Turn(AI &ai, Field &field)
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
	PrintAsciLogo();
	srand(time(NULL));
	int level_val;
	bool game_on = true;
	while (game_on)
	{
		Field field(FIELD_SIDE, std::vector<int>(FIELD_SIDE, 0));

		do
		{
			std::cout << "Please enter level of difficulty (1, 2, 3): ";
			std::cin >> level_val;
		} while (level_val > 3 || level_val < 1);

			AI *ai = NULL;

		switch (level_val)
		{
		case 1:
			ai = new AI_Lvl1(field);
			break;
		case 2:
			ai = new AI_Lvl2(field);
			break;
		case 3:
			ai = new AI_Lvl3(field);
			break;
		}
		char input;
		int hows_first = rand() % 2;
		while (1)
		{
			if (hows_first)
			{
				if (AI_Turn(*ai, field) == GAME_ENDED)
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
				if (AI_Turn(*ai, field) == GAME_ENDED)
					break;
			}
		}

		char go_on;
		std::cout << "Play again? [y/n]: ";
		std::cin >> go_on;
		if (go_on != 'y')
		{
			game_on = false;
		}
	}
	return 0;

}
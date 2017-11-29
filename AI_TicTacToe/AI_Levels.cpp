#include "AI_Levels.h"
#include <cstdlib>
#include <ctime>

using namespace AI_TicTacToe;
//IMPORTANT: PLAYER_MARK(1) is not NULL, it`s name of mark that player puts
//AI_MARK(2) is a name of mark that AI puts (see AI.h for defines)

				/*AI LEVEL 1*/
//--------------------------------------------------------------------------------------------------
AI_Lvl1::AI_Lvl1(Field &field):AI(field){}

void AI_Lvl1::MakeMyMark() //here AI will put a mark if there`s no threat of loss during next turn  
{
	int x, y;

	srand(time(NULL));
	do
	{
		x = rand() % FIELD_SIDE;
		y = rand() % FIELD_SIDE;
	} 
	while (!TryToPutMark(x, y)); //try to put mark, if not empty -- try again
}

void AI_Lvl1::MakeATurn()
{
	_turns_num++;
	if (_turns_num == 1) //first turn, so we have no need to check opponent marks
	{
		MakeMyMark();
		return;
	}

	MakeMyMark();
}


			/*AI LEVEL 2*/
//--------------------------------------------------------------------------------------------------
AI_Lvl2::AI_Lvl2(Field &field) :AI(field) {}

void AI_Lvl2::MakeFirstMark()
{
	if (!TryToPutMark(1, 1)) //try to put mark at the center
	{
		srand(time(NULL));
		int x = rand() % FIELD_SIDE; //x and y from 0 to 2
		int y = rand() % FIELD_SIDE;
		TryToPutMark(x, y); //find empty cell
	}
}

void AI_Lvl2::MakeMyMark() //here AI will put a mark if there`s no threat of loss during next turn  
{
	//first check area near previous mark
	//here we check all cells (around)near last marked cell
	for (int cell_near_x = -1; cell_near_x <= 1; ++cell_near_x)
		for (int cell_near_y = -1; cell_near_y <= 1; ++cell_near_y)
		{
			if (!cell_near_x && !cell_near_y) //if it`s a last cell
				continue;
			//here we specify the position of sell near last marked cell
			int second_cell_x = _last_mark_x + cell_near_x;
			int second_cell_y = _last_mark_y + cell_near_y;
			//next I check is cell I`m looking at out of bounds
			if (AI_Helper::IsCellInbound(second_cell_x, second_cell_y))
				if (!_field[second_cell_x][second_cell_y])
				{
					//if it`s true, we have too
					//check next cell in a row after _field[second_cell_x][second_cell_y]
					//in order to put mark there in next turn and win

					//first we find a offset vector
					int offset_x = second_cell_x - _last_mark_x;
					int offset_y = second_cell_y - _last_mark_y;

					//possible future opponent game winning mark
					if (AI_Helper::IsCellInbound(second_cell_x + offset_x, second_cell_y + offset_y) &&
						(!_field[second_cell_x + offset_x][second_cell_y + offset_y]))
					{
						//if cell after second is empty, we have opportunity to win in next turn
						TryToPutMark(second_cell_x, second_cell_y);
						return;
					}

				}
		}

	//if there`s no place with two empty cells in a row near last cell --> AI just use one of free cells near
	//10 times AI trys to put a mark near last mark
	int x, y;
	int ten_times = 10;
	srand(time(NULL));
	do //find empty cell near
	{
		x = rand() % FIELD_SIDE;
		y = rand() % FIELD_SIDE;
		//codition in IF below checks is a random cell is near our cell
		if (((abs(_last_mark_x - x) == 2) || (abs(_last_mark_y - y) == 2)) && ten_times > 0)
			continue;
	} while (!TryToPutMark(x, y));
}

void AI_Lvl2::MakeATurn()
{
	_turns_num++;
	if (_turns_num == 1)
	{
		MakeFirstMark(); //try to possess a center cell
		return;
	}
	if (TryToWin()) //if AI can finish the game
	{
		return;
	}

	if (TryToObstructOpponent()) //if opponent has 2 in a row AI will obstruct
	{
		return;
	}

	MakeMyMark();
}

			/*AI LEVEL 2*/
//--------------------------------------------------------------------------------------------------
AI_Lvl3::AI_Lvl3(Field & field):AI_Lvl2(field) {} 

void AI_Lvl3::MakeMyMark()
{
	AI_Lvl2::MakeMyMark();
}

void AI_Lvl3::MakeFirstMark()
{
	if (!TryToPutMark(1, 1)) //try to put mark at the center
	{
		OccupyCornerCell();
	}
}

bool AI_Lvl3::MakeSecondMark()
{
	if ( _field[1][1] == AI_MARK)
	{
		if (GetPlayerMarksNum() == 2)
		{
			if (IsAnyCornerCellMarked())
			{
				OccupySideCell();
			}
			else
			{
				PutMarkNearOpponentsMark();
			}
		}
		else if (GetPlayerMarksNum() == 1)
		{
			OccupyCornerCell();
		}

		return true;
	}

	return false;
}

void AI_Lvl3::OccupyCornerCell()
{
	int x, y;
	srand(time(NULL));
	do 
	{
		x = rand() % FIELD_SIDE;
		y = rand() % FIELD_SIDE;

		//if not corner (x or y == 1) --> continue
	} while ( ((x == 1) || (y == 1)) || !TryToPutMark(x, y));
}

void AI_Lvl3::OccupySideCell()
{
	int x, y;
	srand(time(NULL));
	do
	{
		x = rand() % FIELD_SIDE;
		y = rand() % FIELD_SIDE;

		//if not side --> continue
	} while (!((x == 1 && y != 1) || (x != 1 && y == 1)) || !TryToPutMark(x, y));
}

void AI_Lvl3::PutMarkNearOpponentsMark()
{
	int opponent_mark_x;
	int opponent_mark_y;

	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
		{
			if (_field[i][j] == PLAYER_MARK)
			{

				opponent_mark_x = i;
				opponent_mark_y = j;
				if (TryToPutMark(i - 1, j))
					return;
				else if (TryToPutMark(i + 1, j))
					return;
				else if (TryToPutMark(i, j - 1))
					return;
				else if (TryToPutMark(i, j + 1))
					return;

			}
		}
	}
}

bool AI_Lvl3::IsAnyCornerCellMarked()
{
	if ((_field[0][0] == PLAYER_MARK) ||
		(_field[0][2] == PLAYER_MARK) ||
		(_field[2][0] == PLAYER_MARK) ||
		(_field[2][2] == PLAYER_MARK))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int AI_Lvl3::GetPlayerMarksNum()
{
	int num = 0;
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
		{
			if (_field[i][j] == PLAYER_MARK)
				++num;
		}
	}
	return num;
}

void AI_Lvl3::MakeATurn()
{
	
	_turns_num++;
	if (_turns_num == 1)
	{
		MakeFirstMark(); //try to possess a center cell or corner cell
		return;
	}
	
	if (TryToWin()) //if AI can finish the game
	{
		return;
	}

	if (TryToObstructOpponent()) //if opponent has 2 in a row AI will obstruct
	{
		return;
	}

	if (_turns_num == 2)
	{
		if (MakeSecondMark()) //try to possess a corner cell or side cell
			return;
	}

	MakeMyMark();
}
#include "AI_Levels.h"
#include <cstdlib>
#include <ctime>

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

	if (TryToObstructOpponent()) //if opponent has 2 in a row AI will obstruct
	{
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
			if (IsCellInbound(second_cell_x, second_cell_y))
				if (!_field[second_cell_x][second_cell_y])
				{
					//if it`s true, we have too
					//check next cell in a row after _field[second_cell_x][second_cell_y]
					//in order to put mark there in next turn and win

					//first we find a offset vector
					int offset_x = second_cell_x - _last_mark_x;
					int offset_y = second_cell_y - _last_mark_y;

					//possible future opponent game winning mark
					if (IsCellInbound(second_cell_x + offset_x, second_cell_y + offset_y) &&
						(!_field[second_cell_x + offset_x][second_cell_y + offset_y]))
						{
							//if cell after second is empty, we have opportunity to win in next turn
							TryToPutMark(second_cell_x, second_cell_y);
							return;
						}

				}
		}

	//if there`s no place with two empty cells in a row near last cell --> AI just use one of free cells near
	//THERE ARE ALWAYS A FREE CELL NEAR
	int x, y;
	srand(time(NULL));
	do //find empty cell near
	{
		do
		{
			x = rand() % FIELD_SIDE;
			y = rand() % FIELD_SIDE;
			//codition in WHILE below checks is a random cell is near our cell
		} while ((abs(_last_mark_x - x) == 2) || (abs(_last_mark_y - y) == 2));
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

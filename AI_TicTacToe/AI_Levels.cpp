#include "AI_Levels.h"
#include <cstdlib>
#include <ctime>

//IMPORTANT: ZERO(1) is not NULL, it`s name of mark that player puts
//CROSS(2) is a name of mark that AI puts (see AI.h for defines)

AI_Lvl1::AI_Lvl1(int ** field):AI(field){}

bool AI_Lvl1::CheckOpponentMarks()
{
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
			if (_field[i][j] == ZERO)
			{
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
						if (isCellInbound(second_cell_x, second_cell_y))
							if (_field[second_cell_x][second_cell_y] == ZERO) //if it`s true, we have too			|x|_|_|	|x|_|_|
							{												  //check next cell in a row after them	|x|_|_|	|_|X|_|
																			  //									|_|_|_|	|_|_|_|	
								//first we find a offset vector
								int offset_x = second_cell_x - i,
									offset_y = second_cell_y - j;
								
								//check is cell after second_cell is free, if free --> put our mark there 
								if (isCellInbound(second_cell_x + offset_x, second_cell_y + offset_y)) //possible future opponent game winning mark
									if (TryToPutMark(second_cell_x + offset_x, second_cell_y + offset_y))
										return true;
							}
							else if(_field[second_cell_x][second_cell_y] != CROSS) //if the cell near current exist,	|x|_|_|	|x|_|_| 
																			  //but it`s empty and not filled by AI,	|_|_|_|	|_|_|_|
																			  //there can be situation like this:		|x|_|_|	|_|_|x|
							{
								//first we find a offset vector
								int offset_x = second_cell_x - i,
									offset_y = second_cell_y - j;

								//now offset can be implemented in two directions
								if (isCellInbound(second_cell_x + offset_x, second_cell_y + offset_y)) //possible future opponent game winning mark
									if (_field[second_cell_x + offset_x][second_cell_y + offset_y] == ZERO)
									{
										PutMark(second_cell_x, second_cell_y);
										return true;
									}
							}
					}
			}
	}
	return false;
}

void AI_Lvl1::MakeMyMark() //here AI will put a mark if there`s no threat of loss during next turn  
{
	srand(time(NULL));
	int x = rand() % FIELD_SIDE; //x and y from 0 to 2
	int y = rand() % FIELD_SIDE;
	while (!TryToPutMark(x, y)) //find empty cell
	{
		x = rand() % FIELD_SIDE;
		y = rand() % FIELD_SIDE;
	}

}

void AI_Lvl1::MakeFirstMark()
{
	srand(time(NULL));
	int random_position_x = rand() % FIELD_SIDE,
		random_position_y = rand() % FIELD_SIDE;
	_field[random_position_x][random_position_y] = CROSS;
}

void AI_Lvl1::MakeATurn()
{
	_turns_num++;
	if (_turns_num == 1)
	{
		MakeFirstMark(); //TODO: replace with MakeMyMark(); 
		//for this difficulty level it do the same as MakeMyMark(), but for other levels it would look like this
		return;
	}

	if (CheckOpponentMarks()) //if opponent has 2 in a row AI will obstruct
		return;

	MakeMyMark();
}

#include "AI_Levels.h"
#include <cstdlib>
#include <ctime>

//IMPORTANT: ZERO(1) is not NULL, it`s name of mark that player puts
//CROSS(2) is a name of mark that AI puts (see AI.h for defines)

AI_Lvl1::AI_Lvl1(int ** field):AI(field){}

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
		MakeMyMark();
		return;
	}

	if (CheckOpponentMarks()) //if opponent has 2 in a row AI will obstruct
		return;

	MakeMyMark();
}

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

	if (TryToInterruptOpponent()) //if opponent has 2 in a row AI will obstruct
		return;

	MakeMyMark();
}
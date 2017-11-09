#pragma once

#include "AI.h"

class AI_Lvl1 : public AI
{
public:
	AI_Lvl1(int **field);
	virtual void MakeATurn();

private:
	//virtual bool CanWinNow() { return false; } //this AI level just put random located marks
	virtual bool CheckOpponentMarks();
	virtual void MakeMyMark();
	virtual void MakeFirstMark();
};
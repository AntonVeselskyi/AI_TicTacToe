#pragma once

#include "AI.h"

class AI_Lvl1 : public AI
{
public:
	explicit AI_Lvl1(Field &field);
	virtual void MakeATurn() override;

private:
	virtual void MakeMyMark() override;
	virtual void MakeFirstMark() override {}
};



class AI_Lvl2 : public AI
{
public:
	explicit AI_Lvl2(Field &field);
	virtual void MakeATurn() override;

private:
	virtual void MakeMyMark() override;
	virtual void MakeFirstMark() override;
};
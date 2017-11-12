#pragma once

#include <vector>
#define FIELD_SIDE (3)
#define AI_MARK	(2) //AI mark
#define PLAYER_MARK	(1) //Player mark
typedef std::vector<std::vector<int> > Field;

//AI --- will put an array with '2', when player will use '1'
class AI
{
public:
	AI(Field &field);
	virtual ~AI() = default;
	virtual void MakeATurn() = 0;
	static bool IsCellInbound(int x, int y); //is Cell (x,y) belongs to field
protected:
	Field &_field; //3x3 array
	int _turns_num = 0; //for now if it`s first turn (and for statistics)
	int _last_mark_x = 0; //last mark is needed for AI to know were to continue 
	int _last_mark_y = 0;

	bool TryToPutMark(int x, int y);//try to write AI_MARK in (X,Y) position in array

	virtual bool TryToWinNow(); 
	virtual bool TryToInterruptOpponent();
	virtual void MakeMyMark() = 0;
	virtual void MakeFirstMark() = 0;

};


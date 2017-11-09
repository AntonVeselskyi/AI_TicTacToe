#pragma once

#define FIELD_SIDE 3
#define CROSS	2 //AI mark
#define ZERO	1 //Player mark
class AI
{
public:
	AI(int **field);
	virtual ~AI();
	virtual void MakeATurn() = 0;
	static bool isCellInbound(int x, int y); //is Cell (x,y) belongs to field
protected:
	int **_field; //3x3 array
	int _turns_num = 0; //for now if it`s first turn (and for statistics)
	int _last_mark_x = 0; //last mark is needed for AI to know were to continue 
	int _last_mark_y = 0;

	void PutMark(int x, int y); //write '0' somewhere in array
	bool TryToPutMark(int x, int y);

	virtual bool CanWinNow(); //check if AI can win by puting ONE LAST MARK
	virtual bool CheckOpponentMarks(); //check if we need to interrupt
	virtual void MakeMyMark() = 0;
	virtual void MakeFirstMark() = 0;

}; //AI --- will put an array with '2', when player will use '1'


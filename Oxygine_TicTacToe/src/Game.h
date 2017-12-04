#pragma once
#include "oxygine-flow.h"
#include "oxygine-framework.h"
#include <vector>
using Field = std::vector<std::vector<int> >;
using namespace oxygine;

DECLARE_SMART(Game, spGame);
const float MARK_OFFSET = 10;



class Game : public flow::Scene
{
public:
    explicit Game();
	void StartGameLoop(); //main game loop

private:
	// set tictactoe field optimal for user screen
	void DrawBoard(); 
	void PutMarkAtPoint(int x, int y, int mark); //put sprite into cell
	void PutMarkAtPointAnimated(int x, int y, int mark);//put sprite into cell and animate it
	void RemoveAllMarks();
	void ShowWinAnimation(const Field &field) const;
	char ParseTouchPoint(const int x, const int y) const; //screen touch point into char-code for input
	char GetClickOnStage() const; //wait for player click/tap

	void UpdateAll() const; //update OXYGINE engine stuff

	inline void SetDifficulty(int n) { _level_of_difficulty = n; };

	Game & operator=(const Game &) = delete;
	Game(const Game &) = delete;

	std::vector<std::vector<spSprite> > _marks;
	Vector2 _stage_size;
	Vector2 _center;
	float _line_length = 0;
	int _level_of_difficulty = 0;

};
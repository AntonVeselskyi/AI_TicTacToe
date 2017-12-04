#pragma once
#define GAME_ENDED (1)
#define GAME_CONTINUE (0)
#define WRONG_INPUT (-1)

#include "AI_Levels.h"
#include <utility>
#define  NOMINMAX
#include <Windows.h>
#include <cstdlib>
#include <ctime>
namespace AI_TicTacToe
{
	DllExport bool PutPlayerMark(Field &field, std::pair<int, int> point);
	DllExport int Player_Turn(Field &field, char input, bool show_filed = true);
	DllExport int AI_Turn(AI &ai, Field &field);
	DllExport bool ImplementPlayerInput(char input, Field &field);
	DllExport bool IsGameEnded(const Field &field);
	DllExport std::pair<int,int> FieldsDiff(const Field &a, const Field &b);
	DllExport Field& GetField();
}
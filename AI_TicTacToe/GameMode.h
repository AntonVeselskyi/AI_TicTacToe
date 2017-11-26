#pragma once

#include "AI_Levels.h"
#include <utility>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

DllExport void PutPlayerMark(Field &field, std::pair<int, int> point);
DllExport int Player_Turn(Field &field, char input, bool show_filed = true);
DllExport int AI_Turn(AI &ai, Field &field);
DllExport void ImplementPlayerInput(char input, Field &field);
DllExport bool IsGameEnded(const Field &field);
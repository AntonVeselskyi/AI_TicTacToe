#include "AI.h"

using namespace AI_TicTacToe;

bool AI_Helper::IsCellInbound(int x, int y)
{
	if ((x <= 2) && (x >= 0) && (y <= 2) && (y >= 0))
	{
		return true;
	}

	return false;
}

AI::AI(Field &field) : _field(field){}


bool AI::TryToPutMark(int x, int y)
{
	//if cell inbound and  == 0, we can mark it
	if (AI_Helper::IsCellInbound(x,y) && _field[x][y] == 0) 
	{
		_field[x][y] = AI_MARK;
		_last_mark_x = x;
		_last_mark_y = y;
		return true;
	}
	return false;
}

bool AI::TryToWin()
{
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
		{
			if (_field[i][j] == AI_MARK)
			{
				//here we check all cells (around)near current
				//(cell_near_x == 0 && cell_near_y == 0) -->it`s current cell
				for (int cell_near_x = -1; cell_near_x <= 1; ++cell_near_x)
					for (int cell_near_y = -1; cell_near_y <= 1; ++cell_near_y)
					{
						if (!cell_near_x && !cell_near_y) //if it`s current cell
							continue;
						//here we specify the position of sell near [i][j] cell
						int second_cell_x = i + cell_near_x;
						int second_cell_y = j + cell_near_y;
						//next I check is cell I`m looking at out of bounds
						if (AI_Helper::IsCellInbound(second_cell_x, second_cell_y))
						{
							if (_field[second_cell_x][second_cell_y] == AI_MARK)
							{
								//if it`s true, we have to
								//check next cell in a row after them 

								//first we find a offset
								int offset_x = second_cell_x - i;
								int offset_y = second_cell_y - j;

								if (AI_Helper::IsCellInbound(second_cell_x + offset_x, second_cell_y + offset_y) &&
									TryToPutMark(second_cell_x + offset_x, second_cell_y + offset_y))
								{
									return true;
								}
							}
							else if (_field[second_cell_x][second_cell_y] != PLAYER_MARK)
							{
								//if the cell near current exist, 
								//but it`s empty and not filled by player,
								//there can be situation like this:

								//first we have to find an offset
								int offset_x = second_cell_x - i;
								int offset_y = second_cell_y - j;

								if (AI_Helper::IsCellInbound(second_cell_x + offset_x, second_cell_y + offset_y) &&
									_field[second_cell_x + offset_x][second_cell_y + offset_y] == AI_MARK)
								{
									//if we have |x||_||x| situation
									TryToPutMark(second_cell_x, second_cell_y);
									return true; 
								}
							}
						}
					}
			}
		}
	}
	return false;
}

bool AI::TryToObstructOpponent()
{
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
			if (_field[i][j] == PLAYER_MARK)
			{
				//here we check all cells (around)near current
				for (int cell_near_x = -1; cell_near_x <= 1; ++cell_near_x)
					for (int cell_near_y = -1; cell_near_y <= 1; ++cell_near_y)
					{
						if (!cell_near_x && !cell_near_y) //if it`s current cell
							continue;
						//here we specify the position of sell near [i][j] cell
						int second_cell_x = i + cell_near_x;
						int second_cell_y = j + cell_near_y;
						//next I check is cell I`m looking at out of bounds
						if (AI_Helper::IsCellInbound(second_cell_x, second_cell_y))
							if (_field[second_cell_x][second_cell_y] == PLAYER_MARK)
							{
								//if it`s true, we have too
								//check next cell in a row after them	

								//first we find a offset vector
								int offset_x = second_cell_x - i;
								int offset_y = second_cell_y - j;

								//check is cell after second_cell is free, if free --> put our mark there
								//possible future opponent game winning mark
								if (AI_Helper::IsCellInbound(second_cell_x + offset_x, second_cell_y + offset_y) &&
									TryToPutMark(second_cell_x + offset_x, second_cell_y + offset_y))
									return true;
							}
							else if (_field[second_cell_x][second_cell_y] != AI_MARK)
							{
								//if the cell near current exist,
								//but it`s empty and not filled by AI,
								//there can be situation like this:

								//first we find a offset vector
								int offset_x = second_cell_x - i;
								int offset_y = second_cell_y - j;

								//possible future opponent game winning mark
								if (AI_Helper::IsCellInbound(second_cell_x + offset_x, second_cell_y + offset_y) &&
									_field[second_cell_x + offset_x][second_cell_y + offset_y] == PLAYER_MARK)
									{
										TryToPutMark(second_cell_x, second_cell_y);
										return true;
									}
							}
					}
			}
	}
	return false;
}

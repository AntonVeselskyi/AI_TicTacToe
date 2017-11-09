#include "AI.h"



AI::AI(int **field) : _field(field){}


AI::~AI(){}

void AI::PutMark(int x, int y)
{
	_field[x][y] = CROSS;
	_last_mark_x = x;
	_last_mark_y = y;
}

bool AI::TryToPutMark(int x, int y)
{
	if (!_field[x][y]) //if cell == 0, we can mark it
	{
		PutMark(x, y);
		return true;
	}
	return false;
}

bool AI::isCellInbound(int x, int y) //checks is cell inside 3x3 area
{
	if ((x) <= 2 && (x) >= 0 && (y) <= 2 && (y) >= 0)
	return true;

	return false;
}

bool AI::CanWinNow()
{
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
			if (_field[i][j] == CROSS) //CROSS is AI symbol
			{
				//here we check all cells (around)near current
				for (int a = -1; a <= 1; ++a)
					for (int b = -1; b <= 1; ++b)
					{
						if (!a && !b) //if it`s current cell
							continue;
						//here we specify the position of sell near [i][j] cell
						int second_cell_x = i + a,
							second_cell_y = j + b;
						//next I check is cell I`m looking at out of bounds
						if (isCellInbound(second_cell_x, second_cell_y))
							if (_field[second_cell_x][second_cell_y] == CROSS) 
							{												  
								//if it`s true, we have too             |x|_|_|	|x|_|_|
								//check next cell in a row after them   |x|_|_|	|_|X|_|
								//                                      |_|_|_|	|_|_|_|

								//first we find a offset vector
								int offset_x = second_cell_x - i,
									offset_y = second_cell_y - j;

								//check is cell after second_cell is free, if free --> put our mark there 
								if (isCellInbound(second_cell_x + offset_x, second_cell_y + offset_y)) 
									if (TryToPutMark(second_cell_x + offset_x, second_cell_y + offset_y))
										return true; //our game winning mark
							}
							else if (_field[second_cell_x][second_cell_y] != ZERO) 														
							{
								//if the cell near current exist,           |x|_|_|	|x|_|_| 
								//but it`s empty and not filled by player,  |_|_|_|	|_|_|_|
								//there can be situation like this:         |x|_|_|	|_|_|x|

								//first we find a offset vector
								int offset_x = second_cell_x - i,
									offset_y = second_cell_y - j;

								//now offset can be implemented in two directions
								if (isCellInbound(second_cell_x + offset_x, second_cell_y + offset_y)) 
									if (_field[second_cell_x + offset_x][second_cell_y + offset_y] == ZERO)
									{
										PutMark(second_cell_x, second_cell_y);
										return true; //our game winning mark
									}
							}
					}
			}
	}
	return false;
}

bool AI::CheckOpponentMarks()
{
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
			if (_field[i][j] == ZERO)
			{
				//here we check all cells (around)near current
				for (int a = -1; a <= 1; ++a)
					for (int b = -1; b <= 1; ++b)
					{
						if (!a && !b) //if it`s current cell
							continue;
						//here we specify the position of sell near [i][j] cell
						int second_cell_x = i + a,
							second_cell_y = j + b;
						//next I check is cell I`m looking at out of bounds
						if (isCellInbound(second_cell_x, second_cell_y))
							if (_field[second_cell_x][second_cell_y] == ZERO)
							{
								//if it`s true, we have too             |x|_|_|	|x|_|_|
								//check next cell in a row after them   |x|_|_|	|_|X|_|
								//                                      |_|_|_|	|_|_|_|	

								//first we find a offset vector
								int offset_x = second_cell_x - i,
									offset_y = second_cell_y - j;

								//check is cell after second_cell is free, if free --> put our mark there
								//possible future opponent game winning mark
								if (isCellInbound(second_cell_x + offset_x, second_cell_y + offset_y))
									if (TryToPutMark(second_cell_x + offset_x, second_cell_y + offset_y))
										return true;
							}
							else if (_field[second_cell_x][second_cell_y] != CROSS)
							{
								//if the cell near current exist,       |x|_|_|	|x|_|_|
								//but it`s empty and not filled by AI,  |_|_|_|	|_|_|_|
								//there can be situation like this:     |x|_|_|	|_|_|x|

								//first we find a offset vector
								int offset_x = second_cell_x - i,
									offset_y = second_cell_y - j;

								//possible future opponent game winning mark
								if (isCellInbound(second_cell_x + offset_x, second_cell_y + offset_y))
									if (_field[second_cell_x + offset_x][second_cell_y + offset_y] == ZERO)
									{
										PutMark(second_cell_x, second_cell_y);
										return true;
									}
							}
					}
			}
	}
	return false;
}

#include "AI_TicTacToe/GameMode.h"
#include "Game.h"
#include "Dialogs.h"
#include "res.h"



Game::Game() : _marks(FIELD_SIDE, std::vector<spSprite>(FIELD_SIDE, NULL))
{
	_stage_size = { getStage()->getWidth(), getStage()->getHeight() };
	
	_center = { _stage_size.x / 2, _stage_size.y / 2 };

	DrawBoard();

	setName("TicTacToe");
}

void Game::DrawBoard()
{
	if(_stage_size.x < _stage_size.y)	//horisontal screen
		_line_length = 5 * getStage()->getWidth() / 7;
	else   //vertical screen
		_line_length = 5 * getStage()->getHeight() / 7;

	for (int i = 0; i < 4; ++i)
	{
		ColorRectSprite *line = new ColorRectSprite;
		
		line->setWidth(_line_length);
		line->setHeight(10);
		line->attachTo(getStage());
		switch (i)
		{
		case 0:					/*to be at _center*/
			line->setPosition(_center.x - _line_length / 2 , _center.y - _line_length / 5);
			break;
		case 1:
			line->setPosition(_center.x - _line_length / 2, _center.y + _line_length / 5);
			break;
		case 2:
			line->setPosition(_center.x - _line_length / 5, _center.y - _line_length / 2);
			line->setRotationDegrees(90.0);
			break;
		case 3:
			line->setPosition(_center.x + _line_length / 5, _center.y - _line_length / 2);
			line->setRotationDegrees(90.0);
			break;
		}
		
	}

}

//ATTENTION: FUNCTION THAT HARD TO LOOK AT( WORKS WITH CORDINATES)
void Game::PutMarkAtPoint(int x, int y, int mark)
{
	Vector2 point_to_put_image = {0, 0};
	if (_marks[x][y] != NULL)
	{
		return;
	}

	_marks[x][y] = new Sprite;


	if (x == 0)
	{
		if (y == 0)
		{
			point_to_put_image.x = _center.x - _line_length / 2 - MARK_OFFSET;
			point_to_put_image.y = _center.y - _line_length / 2 - MARK_OFFSET;
		}
		else if (y == 1)
		{
			point_to_put_image.x = _center.x - _line_length / 6;
			point_to_put_image.y = _center.y - _line_length / 2 - MARK_OFFSET;
		}
		else if (y == 2)
		{
			point_to_put_image.x = _center.x + _line_length / 6 + MARK_OFFSET;
			point_to_put_image.y = _center.y - _line_length / 2 - MARK_OFFSET;
		}
	}
	else if (x == 1)
	{
		if (y == 0)
		{
			point_to_put_image.x = _center.x - _line_length / 2 - MARK_OFFSET;
			point_to_put_image.y = _center.y - _line_length / 6;
		}
		else if (y == 1)
		{
			point_to_put_image.x = _center.x - _line_length / 6;
			point_to_put_image.y = _center.y - _line_length / 6;
		}
		else if (y == 2)
		{
			point_to_put_image.x = _center.x + _line_length / 6 + MARK_OFFSET;
			point_to_put_image.y = _center.y - _line_length / 6;
		}
	}
	else if (x == 2)
	{
		if (y == 0)
		{
			point_to_put_image.x = _center.x - _line_length / 2 - MARK_OFFSET;
			point_to_put_image.y = _center.y + _line_length / 6 + MARK_OFFSET;
		}
		else if (y == 1)
		{
			point_to_put_image.x = _center.x - _line_length / 6;
			point_to_put_image.y = _center.y + _line_length / 6 + MARK_OFFSET;
		}
		else if (y == 2)
		{
			point_to_put_image.x = _center.x + _line_length / 6 + MARK_OFFSET;
			point_to_put_image.y = _center.y + _line_length / 6 + MARK_OFFSET;
		}
	}

	if (mark == 1)
	{
		_marks[x][y]->setResAnim(res::ui.getResAnim("skull"));
		
	}
	else if (mark == 2)
	{
		_marks[x][y]->setResAnim(res::ui.getResAnim("coin"));
	}

	_marks[x][y]->setHeight(_line_length / 3);
	_marks[x][y]->setWidth(_line_length / 3);
	_marks[x][y]->setPosition(point_to_put_image.x, point_to_put_image.y);
	_marks[x][y]->attachTo(getStage());
}
void Game::PutMarkAtPointAnimated(int x, int y, int mark)
{
	PutMarkAtPoint(x, y, mark);

	float angle = 360.0f * (rand() % 2 ? -1 : 1);
	
	if (mark == AI_MARK)
	{
		_marks[x][y]->setVisible(false);
		spTween wait = _marks[x][y]->addTween(TweenDummy(), 1000, 1);
		while (!wait->isDone())
		{
			UpdateAll();
		}
		_marks[x][y]->setVisible(true);
	}
	_marks[x][y]->addTween(Actor::TweenRotationDegrees(angle), 700, 1);

}

void Game::RemoveAllMarks()
{
	//------CLEAN MARKS FROM FIELD --------------
	for (int i = 0; i < FIELD_SIDE; ++i)
		for (int j = 0; j < FIELD_SIDE; ++j)
		{
			if (_marks[i][j] != NULL)
			{
				_marks[i][j]->detach();
				_marks[i][j] = NULL;
			}
		}
}

void Game::ShowWinAnimation(const Field &field) const
{
	//find 3 winning marks
	int field_mark;
	for (int i = 0; i < FIELD_SIDE; ++i)
	{
		for (int j = 0; j < FIELD_SIDE; ++j)
			if (field[i][j] != NULL)
			{
				field_mark = field[i][j];
				//here we check all cells (around)near current
				for (int cell_near_x = -1; cell_near_x <= 1; ++cell_near_x)
					for (int cell_near_y = -1; cell_near_y <= 1; ++cell_near_y)
					{
						if (!cell_near_x && !cell_near_y) //if it`s current cell
							continue;
						//here we specify the position of sell near [i][j] cell
						int second_cell_x = i + cell_near_x;
						int second_cell_y = j + cell_near_y;

						if (AI_TicTacToe::AI_Helper::IsCellInbound(second_cell_x, second_cell_y) &&
							(field[second_cell_x][second_cell_y] == field_mark))
						{
							//if it`s true, we have too
							//check next cell in a row after them

							//first we find a offset vector
							int offset_x = second_cell_x - i;
							int offset_y = second_cell_y - j;

							//check is cell after second_cell is free, if free --> put our mark there 
							if (AI_TicTacToe::AI_Helper::IsCellInbound(second_cell_x + offset_x, second_cell_y + offset_y))
								if (field[second_cell_x + offset_x][second_cell_y + offset_y] == field_mark) //GAME WON
								{
									_marks[i][j]->addTween(Actor::TweenScale(1.1f), 700, 2, true);
									_marks[second_cell_x][second_cell_y]->addTween(Actor::TweenScale(1.1f), 700, 2, true);
									spTween wait = 
									_marks[second_cell_x + offset_x][second_cell_y + offset_y]->addTween(Actor::TweenScale(1.1f), 700, 2, true);
									
									while (!wait->isDone())
									{
										UpdateAll();
									}
								}
						}
					}
			}
	}
}

char Game::ParseTouchPoint(const int x, const int y) const
{	
	//find 4 crosspoints
	Vector2 left_top = { _center.x - _line_length / 6, _center.y - _line_length / 6 };
	Vector2 right_top = { _center.x + _line_length / 6, _center.y - _line_length / 6 };
	Vector2 left_bot = { _center.x - _line_length / 6, _center.y + _line_length / 6 };
	Vector2 right_bot = { _center.x + _line_length / 6, _center.y + _line_length / 6 };

	if (x < left_top.x && y < left_top.y)
		return 'q';
	else if (x > left_top.x && x < right_top.x && y < left_top.y)
		return 'w';
	else if (x > right_top.x && y < left_top.y)
		return 'e';
	else if (x < left_bot.x && y <left_bot.y  && y > left_top.y)
		return 'a';
	else if (x > left_bot.x && x < right_bot.x  && y <left_bot.y  && y > left_top.y)
		return 's';
	else if (x > right_bot.x  && y <left_bot.y  && y > left_top.y)
		return 'd';
	else if (x < left_bot.x && y > left_top.y)
		return 'z';
	else if (x > left_bot.x && x < right_bot.x  && y > left_top.y)
		return 'x';
	else if (x > right_bot.x && y > left_top.y)
		return 'c';

	return '0';
}

 char Game::GetClickOnStage() const
{
	static bool wasClicked;
	wasClicked = false;
	static char input;
	input = '0';
	getStage()->addClickListener([&](Event* ev)
	{
		ev->removeListener();
		wasClicked = true;
		input = ParseTouchPoint(((TouchEvent*)ev)->position.x, ((TouchEvent*)ev)->position.y);
	});
	
	while (true)
	{
		UpdateAll();
		if (wasClicked)
			break;
	}

	return input;
}

void Game::StartGameLoop()
{
	using namespace AI_TicTacToe;

	srand(time(NULL));
	bool got_lvl = false;
	bool got_repeat = false;
	bool game_on = true;
	
	char input;
	short p_res = WRONG_INPUT;
	std::pair<int, int> new_mark(-1, -1);

	spLevelDialog diff_dlg = new LevelDialog(_level_of_difficulty);
	spRepeatDialog repeat_dlg = new RepeatDialog(game_on);

	while (game_on)
	{
//------CREATE NEW FIELD---------------------
		Field field(FIELD_SIDE, std::vector<int>(FIELD_SIDE, 0));
		Field tmp_field(FIELD_SIDE, std::vector<int>(FIELD_SIDE, 0));

		RemoveAllMarks();

//------GETTING LEVEL OF DIFFICULTY----------
		got_lvl = false;

		//get level of difficulty
		flow::show(diff_dlg, [&](Event*)
		{
			//result callback here
			got_lvl = true;
		});

		while (!got_lvl)
		{
			UpdateAll();
		}

//------INIT AI------------------------------
		AI *ai = NULL;

		switch (_level_of_difficulty)
		{
		case 1:
			ai = new AI_Lvl1(field);
			break;
		case 2:
			ai = new AI_Lvl2(field);
			break;
		case 3:
			ai = new AI_Lvl3(field);
			break;
		}

//------GAME PROCCESS ITSELF-----------------
		int hows_first = rand() % 2;
		while (1)
		{
			if (hows_first)
			{
				tmp_field = field;
				p_res = AI_Turn(*ai, field);
				new_mark = FieldsDiff(field, tmp_field);
				PutMarkAtPointAnimated(new_mark.first, new_mark.second, AI_MARK);
				UpdateAll();
				if (p_res == GAME_ENDED)
					break;
				
				p_res = WRONG_INPUT;
				tmp_field = field;
				while (p_res == WRONG_INPUT)
				{
					input = GetClickOnStage();
					p_res = Player_Turn(field, input);
				}
				new_mark = FieldsDiff(field, tmp_field);
				PutMarkAtPointAnimated(new_mark.first, new_mark.second, PLAYER_MARK);
				UpdateAll();
				if (p_res == GAME_ENDED)
					break;

			}
			else
			{
				p_res = WRONG_INPUT;
				tmp_field = field;
 				while (p_res == WRONG_INPUT)
				{
					input = GetClickOnStage();
					p_res = Player_Turn(field, input);
				}
				new_mark = FieldsDiff(field, tmp_field);
				PutMarkAtPointAnimated(new_mark.first, new_mark.second, PLAYER_MARK);
				UpdateAll();
				if (p_res == GAME_ENDED)
					break;

				tmp_field = field;
				p_res = AI_Turn(*ai, field);
				new_mark = FieldsDiff(field, tmp_field);
				PutMarkAtPointAnimated(new_mark.first, new_mark.second, AI_MARK);
				UpdateAll();
				if (p_res == GAME_ENDED)
					break;
			}
		}

		delete ai;

		//delay after last mark
		spTween wait = _marks[new_mark.first][new_mark.second]->addTween(TweenDummy(), 1000, 1);
		while (!wait->isDone())
		{
			UpdateAll();
		}

		ShowWinAnimation(field);

//------REPEAT REQUEST-----------------------
		got_repeat = false;

		//get level of difficulty
		//repeat_dlg->
		RemoveAllMarks();

		flow::show(repeat_dlg, [&](Event*)
		{
			//result callback here
			got_repeat = true;
		});

		while (!got_repeat)
		{
			UpdateAll();
		}

	}
}

void Game::UpdateAll() const
{
	core::update();
	getStage()->update();
	if (core::beginRendering())
	{
		Color clearColor(32, 32, 32, 255);
		Rect viewport(Point(0, 0), core::getDisplaySize());
		// Render all actors inside the stage. Actor::render will also be called for all its children
		getStage()->render(clearColor, viewport);

		core::swapDisplayBuffers();
	}
}
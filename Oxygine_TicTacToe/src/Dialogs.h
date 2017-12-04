#pragma once
#include "oxygine-flow.h"
#include "oxygine-framework.h"
#include <vector>
#include "res.h"
using Field = std::vector<std::vector<int> >;
using namespace oxygine;


DECLARE_SMART(LevelDialog, spLevelDialog);
DECLARE_SMART(RepeatDialog, spRepeatDialog);

class LevelDialog : public flow::Scene
{
public:
	explicit LevelDialog(int &lvl) : lvl_to_set(lvl)
	{
		setName("LevelDialog");

		_dialog = true;

		Vector2 size_cof_for_view = _holder->getSize() / 10;
		_view = new Box9Sprite;
		_view->setSize(size_cof_for_view.x * 5, size_cof_for_view.y * 3);
		_view->attachTo(_holder);
		_view->setPosition(_holder->getSize() / 2 - _view->getSize() / 2);

		Vector2 size_of_view = _view->getSize();
		const int buttons_Y_offset = size_of_view.y / 2;
		TextStyle style = TextStyle(res::ui.getResFont("main")).withColor(Color::White).alignMiddle();

		for (int i = 0; i < 3; ++i)
		{
			lvl_button[i] = new Button;
			lvl_button[i]->setSize((size_of_view.x / 10.0f * 2), buttons_Y_offset);
			lvl_button[i]->attachTo(_view);

			lvl_text[i] = new TextField();
			//attach it as child to button
			lvl_text[i]->attachTo(lvl_button[i]);
			//centered in lvl_button[i]
			lvl_text[i]->setPosition((lvl_button[i]->getSize() / 2).x - 4, (lvl_button[i]->getSize() / 2).y - 4);

			//initialize lvl_text[i] style
			lvl_text[i]->setStyle(style);
			lvl_text[i]->setText(std::to_string(i + 1));
			lvl_text[i]->setFontSize(_view->getSize().y / 5);
		}

		lvl_button[0]->setPosition((size_of_view.x / 10.0f), buttons_Y_offset);
		lvl_button[1]->setPosition((size_of_view.x / 10.0f * 4.0f), buttons_Y_offset);
		lvl_button[2]->setPosition((size_of_view.x / 10.0f * 7.0f), buttons_Y_offset);

		lvl_button[0]->addEventListener(TouchEvent::CLICK, [=](Event* ev)
		{
			finish();
			flow::update();
			lvl_to_set = 1;
		});
		lvl_button[1]->addEventListener(TouchEvent::CLICK, [=](Event* ev)
		{
			finish();
			flow::update();
			lvl_to_set = 2;
		});

		lvl_button[2]->addEventListener(TouchEvent::CLICK, [=](Event* ev)
		{
			finish();
			flow::update();
			lvl_to_set = 3;
		});

		spTextField main_label = new TextField();
		main_label->setText("Choose level of difficulty");
		main_label->setStyle(style);
		main_label->setStyleColor(Color::Red);
		main_label->attachTo(_view);
		main_label->setPosition(_view->getSize().x / 2, _view->getSize().y / 4);
		main_label->setFontSize(_view->getSize().y / 4);

		flow::TransitionMove::assign(this);

		addEventListener(EVENT_PRE_SHOWING, [=](Event*)
		{
		});
	}

	int &lvl_to_set;
	spActor _view;
	spTextField lvl_text[3];
	spButton lvl_button[3];
};

class RepeatDialog : public flow::Scene
{
public:
	explicit RepeatDialog(bool &repeat_status) : repeat(repeat_status)
	{
		setName("RepeatDialog");

		_dialog = true;

		Vector2 size_cof_for_view = _holder->getSize() / 10;
		_view = new Box9Sprite;
		_view->setSize(size_cof_for_view.x * 5, size_cof_for_view.y * 3);
		_view->attachTo(_holder);
		_view->setPosition(_holder->getSize() / 2 - _view->getSize() / 2);

		Vector2 size_of_view = _view->getSize();
		const int buttons_Y_offset = size_of_view.y / 2;
		TextStyle style = TextStyle(res::ui.getResFont("main")).withColor(Color::White).alignMiddle();

		for (int i = 0; i < 2; ++i)
		{
			repeat_button[i] = new Button;
			repeat_button[i]->setSize((size_of_view.x / 7.0f * 2), buttons_Y_offset);
			repeat_button[i]->attachTo(_view);

			button_text[i] = new TextField();
			//attach it as child to button
			button_text[i]->attachTo(repeat_button[i]);
			//centered in repeat_button[i]
			button_text[i]->setPosition((repeat_button[i]->getSize() / 2).x - 4, (repeat_button[i]->getSize() / 2).y - 4);

			//initialize button_text[i] style
			button_text[i]->setStyle(style);
			button_text[i]->setText(!i ? "Yay" : "No");
			button_text[i]->setFontSize(_view->getSize().y / 5);
		}

		repeat_button[0]->setPosition((size_of_view.x / 7.0f), buttons_Y_offset);
		repeat_button[1]->setPosition((size_of_view.x / 7.0f * 4.0f), buttons_Y_offset);

		repeat_button[0]->addEventListener(TouchEvent::CLICK, [=](Event* ev)
		{
			finish();
			flow::update();
			repeat = true;
		});
		repeat_button[1]->addEventListener(TouchEvent::CLICK, [=](Event* ev)
		{
			finish();
			flow::update();
			repeat = false;
		});

		spTextField main_label = new TextField();
		main_label->setText("Do you want to play again?");
		main_label->setStyle(style);
		main_label->setStyleColor(Color::Red);
		main_label->attachTo(_view);
		main_label->setPosition(_view->getSize().x / 2, _view->getSize().y / 4);
		main_label->setFontSize(_view->getSize().y / 4);

		flow::TransitionMove::assign(this);

		addEventListener(EVENT_PRE_SHOWING, [=](Event*)
		{
		});
	}

	bool &repeat;
	spActor _view;
	spTextField button_text[2];
	spButton repeat_button[2];
};

/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   10:01
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\TestScene.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	TestScene
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Test scene implementation
*********************************************************************/

#include "TestScene.h"
#include "GameManager.h"

TestScene::TestScene():_x(0.0f),_y(0.0f),_speed(50.0f)
{
	GameManager* manager = GameManager::getInstance();
	clan::Canvas& gc = manager->getCanvas();
	_font = new clan::Font(gc, "Tahoma", 30);
	_boatSprite = clan::Sprite::resource(gc, "sprites/boat", manager->getResourceManager());
	_nextScene = NULL;
}

TestScene::~TestScene()
{ delete _font; }

void TestScene::draw()
{
	clan::Canvas& canvas = GameManager::getInstance()->getCanvas();
	//clan::Draw::line(canvas, 0, 110, 640, 110, clan::Colorf::yellow);
	_font->draw_text(canvas, 100, 100, "Hello World!", clan::Colorf::lightseagreen);
	_boatSprite.draw(canvas, _x, _y);
}

void TestScene::update()
{
	clan::InputDevice keyboard = GameManager::getInstance()->getWindow()->get_ic().get_keyboard();
	int dt = GameManager::getInstance()->getDeltaTime();

	if (keyboard.get_keycode(clan::keycode_left))
	{
		_x -= _speed*dt/1000.0f;
#if _DEBUG
		clan::Console::write_line("time_delta_ms = %1", dt);
#endif
	}

	if (keyboard.get_keycode(clan::keycode_right))
	{
		_x += _speed*dt/1000.0f;
#if _DEBUG
		clan::Console::write_line("time_delta_ms = %1", dt);
#endif
	}

	if (keyboard.get_keycode(clan::keycode_up))
	{
		_y -= _speed*dt/1000.0f;
#if _DEBUG
		clan::Console::write_line("time_delta_ms = %1", dt);
#endif
	}

	if (keyboard.get_keycode(clan::keycode_down))
	{
		_y += _speed*dt/1000.0f;
#if _DEBUG
		clan::Console::write_line("time_delta_ms = %1", dt);
#endif
	}

	_boatSprite.update(dt);
}

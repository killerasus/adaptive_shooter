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
	GameManager* manager = GameManager::GetInstance();
	CL_GraphicContext gc = manager->GetWindow()->get_gc();
	_font = new CL_Font(gc, "Tahoma", 30);
	_boatSprite = new CL_Sprite(gc, "sprites/boat", manager->GetResourceManager());
}

TestScene::~TestScene()
{
	delete _font;
	delete _boatSprite;
}

void TestScene::draw()
{
	CL_GraphicContext gc = GameManager::GetInstance()->GetWindow()->get_gc();
	CL_Draw::line(gc, 0, 110, 640, 110, CL_Colorf::yellow);
	_font->draw_text(gc, 100, 100, "Hello World!", CL_Colorf::lightseagreen);
	_boatSprite->draw(gc, _x, _y);
}

void TestScene::update()
{
	CL_InputDevice keyboard = GameManager::GetInstance()->GetWindow()->get_ic().get_keyboard();
	float dt = GameManager::GetInstance()->GetDeltaTime();

	if (keyboard.get_keycode(CL_KEY_LEFT))
	{
		_x -= _speed*dt/1000.0f;
#if _DEBUG
		CL_Console::write_line("time_delta_ms = %1", dt);
#endif
	}

	if (keyboard.get_keycode(CL_KEY_RIGHT))
	{
		_x += _speed*dt/1000.0f;
#if _DEBUG
		CL_Console::write_line("time_delta_ms = %1", dt);
#endif
	}

	if (keyboard.get_keycode(CL_KEY_UP))
	{
		_y -= _speed*dt/1000.0f;
#if _DEBUG
		CL_Console::write_line("time_delta_ms = %1", dt);
#endif
	}

	if (keyboard.get_keycode(CL_KEY_DOWN))
	{
		_y += _speed*dt/1000.0f;
#if _DEBUG
		CL_Console::write_line("time_delta_ms = %1", dt);
#endif
	}

	_boatSprite->update();
}


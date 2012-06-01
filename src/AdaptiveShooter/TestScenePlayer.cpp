/********************************************************************
	created:	2012/06/01
	created:	1:6:2012   5:24
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\TestScenePlayer.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	TestScenePlayer
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include <iostream>
#include <sstream>
#include "TestScenePlayer.h"
#include "GameManager.h"
#include "PlayerModelImpl.h"

TestScenePlayer::TestScenePlayer()
{
	CL_GraphicContext gc = GameManager::getInstance()->getWindow()->get_gc();
	_font = new CL_Font(gc, "Tahoma", 14);
}

TestScenePlayer::~TestScenePlayer()
{
	delete _font;
}

void TestScenePlayer::draw()
{
	CL_GraphicContext gc = GameManager::getInstance()->getWindow()->get_gc();

	/*CL_Draw::line(gc, 0, 110, 640, 110, CL_Colorf::yellow);
	_font->draw_text(gc, 100, 100, "Hello World!", CL_Colorf::lightseagreen);*/

	Player* playerOne = GameManager::getInstance()->getPlayer(0);
	playerOne->draw();

#if _DEBUG
	std::ostringstream text;
	text.precision(4);
	text << "Player " << (playerOne->getPlayerNumber() + 1) << std::endl;
	text << "Firing accuracy = " << playerOne->getPlayerModel()->getTrait(PlayerModelImpl::ACCURACY) << std::endl;
	text << "Lives variation = " << playerOne->getPlayerModel()->getTrait(PlayerModelImpl::LIVES_VARIATION) << std::endl;
	text << "Enemies wasted total = " << playerOne->getPlayerModel()->getTrait(PlayerModelImpl::ENEMIES_WASTED_TOTAL) << std::endl;

	std::string drawableText = text.str();
	float textX = 640.0f - _font->get_text_size(gc, drawableText).width - 10.f; 
	float textY = 110.0f;

	_font->draw_text(gc, textX, textY, drawableText, CL_Colorf::red);
#endif
}

void TestScenePlayer::update()
{
	GameManager* manager = GameManager::getInstance();
	//manager->getAIManager()->update();
	manager->getPlayer(0)->update();

#if _DEBUG

	const float variation = 0.001f;
	float dt = manager->getDeltaTime();
	PlayerModel* model = manager->getPlayer(0)->getPlayerModel();

	CL_InputDevice keyboard = manager->getWindow()->get_ic().get_keyboard();

	if (keyboard.get_keycode(CL_KEY_U))
	{
		model->setTrait(PlayerModelImpl::ACCURACY, model->getTrait(PlayerModelImpl::ACCURACY) + dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_I))
	{
		model->setTrait(PlayerModelImpl::LIVES_VARIATION, model->getTrait(PlayerModelImpl::LIVES_VARIATION) + dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_O))
	{
		model->setTrait(PlayerModelImpl::ENEMIES_WASTED_TOTAL, model->getTrait(PlayerModelImpl::ENEMIES_WASTED_TOTAL) + dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_J))
	{
		model->setTrait(PlayerModelImpl::ACCURACY, model->getTrait(PlayerModelImpl::ACCURACY) - dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_K))
	{
		model->setTrait(PlayerModelImpl::LIVES_VARIATION, model->getTrait(PlayerModelImpl::LIVES_VARIATION) - dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_L))
	{
		model->setTrait(PlayerModelImpl::ENEMIES_WASTED_TOTAL, model->getTrait(PlayerModelImpl::ENEMIES_WASTED_TOTAL) - dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_P))
	{
		model->resetTraits();
	}

#endif
}

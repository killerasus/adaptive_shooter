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
#include "TestEnemy.h"

// Logging tool
#define LOGOG_USE_PREFIX 1
#include "logog.hpp"


TestScenePlayer::TestScenePlayer()
{
	CL_GraphicContext gc = GameManager::getInstance()->getWindow()->get_gc();
	_font = new CL_Font(gc, "Tahoma", 14);

	CL_Rect windowArea = GameManager::getInstance()->getWindow()->get_viewport();

	TestEnemy* enemy = new TestEnemy( 0.0f, 0.0f, 50.0f, 50.0f, "sprites/boat"  );

	// Adjusts enemy position to the horizontal center of the window
	enemy->setPositionX( windowArea.get_width()*0.5f - enemy->getCurrentSprite()->get_width()*0.5f );

	insertEntity( enemy );
	_enemies.push_back( enemy );
}

TestScenePlayer::~TestScenePlayer()
{
	delete _font;

	std::vector<Shot*>::iterator shotIter;

	// Deletes player shots
	for (shotIter = _playerShots.begin(); shotIter != _playerShots.end(); shotIter++)
	{
		delete *shotIter;
	}

	// Deletes enemies shots
	for (shotIter = _enemyShots.begin(); shotIter != _enemyShots.end(); shotIter++)
	{
		delete *shotIter;
	}

	std::vector<Enemy*>::iterator enemyIter;

	// Deletes enemies
	for (enemyIter = _enemies.begin(); enemyIter != _enemies.end(); enemyIter++)
	{
		delete *enemyIter;
	}
}

void TestScenePlayer::draw()
{
	CL_GraphicContext gc = GameManager::getInstance()->getWindow()->get_gc();

	/*CL_Draw::line(gc, 0, 110, 640, 110, CL_Colorf::yellow);
	_font->draw_text(gc, 100, 100, "Hello World!", CL_Colorf::lightseagreen);*/

	Player* playerOne = GameManager::getInstance()->getPlayer(0);
	playerOne->draw();

	// Calls parent draw implementation for drawing entities
	Scene::draw();

#if _DEBUG
	std::ostringstream text;
	text.precision(4);
	text << "Player " << (playerOne->getPlayerNumber() + 1) << std::endl;
	text << "Model = " << playerOne->getPlayerModel()->getName() << std::endl;
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
	Player* player = manager->getPlayer(0);
	float dt = manager->getDeltaTime();
	PlayerModel* model = player->getPlayerModel();

	player->update();

	CL_InputDevice keyboard = manager->getWindow()->get_ic().get_keyboard();

#if _DEBUG

	const float variation = 0.001f;

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

	if (keyboard.get_keycode(CL_KEY_SPACE))
	{

		std::string modelName = model->getName();

		AIManager* aimanager = GameManager::getInstance()->getAIManager();
		aimanager->update();

		LOGOG_INFO( "Player: %d\nStats:\n Accuracy %f\tLives var %f\tEnemies total %f\nModel name before update: %s\nModel name after update: %s\n",
			player->getPlayerNumber() + 1, player->getPlayerModel()->getTrait(PlayerModelImpl::ACCURACY), model->getTrait(PlayerModelImpl::LIVES_VARIATION),
			model->getTrait(PlayerModelImpl::ENEMIES_WASTED_TOTAL),	modelName.c_str(), player->getPlayerModel()->getName().c_str() );
	}

	// Calls parent implementation of update
	Scene::update();
}

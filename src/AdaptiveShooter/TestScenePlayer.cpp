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

	TestEnemy* enemy = new TestEnemy( 0.0f, 0.0f, 50.0f, 50.0f, "sprites/enemy1"  );

	// Adjusts enemy position to the horizontal center of the window
	enemy->setPositionX( windowArea.get_width()*0.5f - enemy->getCurrentSprite()->get_width()*0.5f );

	// Inserts enemy in AIManager control list
	GameManager::getInstance()->getAIManager()->insertAgent( enemy );

	// Inserts enemy in Scene control list
	insertEntity( enemy );

	_enemies.push_back( enemy );
}

TestScenePlayer::~TestScenePlayer()
{
	delete _font;

	std::list<Shot*>::iterator shotIter;

	// Deletes player shots
	for (shotIter = _playerShots.begin(); shotIter != _playerShots.end(); )
	{
		shotIter = _playerShots.erase( shotIter );
	}

	// Deletes enemies shots
	for (shotIter = _enemyShots.begin(); shotIter != _enemyShots.end(); )
	{
		shotIter = _enemyShots.erase( shotIter );
	}

	std::vector<Enemy*>::iterator enemyIter = _enemies.begin();

	// Deletes enemies
	while (enemyIter != _enemies.end())
	{
		enemyIter = _enemies.erase( enemyIter );
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
	text << "Firing accuracy = " << playerOne->getPlayerModel()->getTraitValue( PlayerModelImpl::ACCURACY ) << std::endl;
	text << "Lives variation = " << playerOne->getPlayerModel()->getTraitValue( PlayerModelImpl::LIVES_VARIATION ) << std::endl;
	text << "Enemies wasted wave = " << playerOne->getPlayerModel()->getTraitValue( PlayerModelImpl::ENEMIES_WASTED_WAVE ) << std::endl;
	text << "Enemies wasted total = " << playerOne->getPlayerModel()->getTraitValue( PlayerModelImpl::ENEMIES_WASTED_TOTAL ) << std::endl;

	if (GameManager::getInstance()->getWindow()->get_ic().get_joystick_count() > 0)
	{
		CL_InputDevice joystick = GameManager::getInstance()->getWindow()->get_ic().get_joystick();
		text << "Joystick name = " << joystick.get_name().c_str() << std::endl;

		for (int i = 0; i < joystick.get_button_count(); i++)
		{
			if (joystick.get_keycode( i ))
			{
				text << "Joystick key = " << joystick.get_key_name( i ).c_str() << std::endl;
			}
		}

		for (int i = 0; i < joystick.get_axis_count(); i++)
		{
			text << "Joystick axis " << i << " = " << joystick.get_axis( i ) << std::endl;
		}
	}

	std::string drawableText = text.str();
	float textX = 640.0f - _font->get_text_size(gc, drawableText).width - 10.f; 
	float textY = 110.0f;

	_font->draw_text(gc, textX, textY, drawableText, CL_Colorf::red);
#endif
}

void TestScenePlayer::update()
{
	GameManager* manager = GameManager::getInstance();
	Player* playerOne = manager->getPlayer(0);
	float dt = manager->getDeltaTime();
	PlayerModel* model = playerOne->getPlayerModel();

	// Player updates occur separately because players can drop in or out
	// treating this in entities would be messy
	playerOne->update();

	CL_InputDevice keyboard = manager->getWindow()->get_ic().get_keyboard();

#if _DEBUG

	const float variation = 0.001f;

	if (keyboard.get_keycode(CL_KEY_Y))
	{
		model->setTraitValue(PlayerModelImpl::ACCURACY, model->getTraitValue(PlayerModelImpl::ACCURACY) + dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_U))
	{
		model->setTraitValue(PlayerModelImpl::LIVES_VARIATION, model->getTraitValue(PlayerModelImpl::LIVES_VARIATION) + dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_I))
	{
		model->setTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE, model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE) + dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_O))
	{
		model->setTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL, model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL) + dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_H))
	{
		model->setTraitValue(PlayerModelImpl::ACCURACY, model->getTraitValue(PlayerModelImpl::ACCURACY) - dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_J))
	{
		model->setTraitValue(PlayerModelImpl::LIVES_VARIATION, model->getTraitValue(PlayerModelImpl::LIVES_VARIATION) - dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_K))
	{
		model->setTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE, model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE) - dt*variation);
	}

	if (keyboard.get_keycode(CL_KEY_L))
	{
		model->setTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL, model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL) - dt*variation);
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
			playerOne->getPlayerNumber() + 1, playerOne->getPlayerModel()->getTraitValue(PlayerModelImpl::ACCURACY), model->getTraitValue(PlayerModelImpl::LIVES_VARIATION),
			model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL),	modelName.c_str(), playerOne->getPlayerModel()->getName().c_str() );
	}

	// Calls parent implementation of update, updating all Entities
	Scene::update();

	// Treat playerShots and enemyShots collision and out of bounds
	std::list<Shot*>::iterator shotIt;

	/*for (shotIt = _playerShots.begin(); shotIt != _playerShots.end(); )
	{
		if ((*shotIt)->checkBoundary())
		{
			shotIt++;
		}
		else
		{
			Shot* remove = *shotIt;
			shotIt++;
			removePlayerShot( remove );
			delete remove;
		}
	}*/

	/*for (shotIt = _enemyShots.begin(); shotIt != _enemyShots.end(); )
	{
		if ((*shotIt)->checkBoundary())
		{
			shotIt++;
		}
		else
		{
			Shot* remove = *shotIt;
			shotIt++;
			removeEnemyShot( remove );
			delete remove;
		}
	}*/

	std::vector<Enemy*>::iterator enemyIt;

	CL_CollisionOutline* shot = NULL;
	CL_CollisionOutline* object = NULL;
	bool remove;

	// Player shots colliding with enemies
	for(shotIt = _playerShots.begin(); shotIt != _playerShots.end(); )
	{
		// Checks if inside window boundaries
		if (!(*shotIt)->checkBoundary())
		{
			Shot* remove = *shotIt;
			shotIt++;
			removePlayerShot( remove );
			delete remove;
			continue;
		}

		remove = false;
		shot = (*shotIt)->getCurrentCollisionOutline();

		//Translates outlines to their current sprite position as outlines start in 0,0
		CL_Vec2f pos = (*shotIt)->getPosition();
		shot->set_translation(pos.x, pos.y);

		for (enemyIt = _enemies.begin(); enemyIt != _enemies.end(); enemyIt++)
		{
			object = (*enemyIt)->getCurrentCollisionOutline();
			
			CL_Vec2f posEnemy = (*enemyIt)->getPosition();
			object->set_translation(posEnemy.x, posEnemy.y);

			if (shot->collide( *object ))
			{
				object->set_translation(0.0f, 0.0f);
				remove = true;
				break;
			}

			object->set_translation(0.0f, 0.0f);
		}

		shot->set_translation(0.0f, 0.0f);

		if (remove)
		{
			Shot* shotRemove = (*shotIt);
			shotIt++;
			removePlayerShot( shotRemove );
			delete shotRemove;
		} 
		else
		{
			shotIt++;
		}
		
	}

	// As currently there is just one player...
	object = playerOne->getCurrentCollisionOutline();
	object->set_translation( playerOne->getPosition().x, playerOne->getPosition().y );

	// Enemies shots colliding with player
	for(shotIt = _enemyShots.begin(); shotIt != _enemyShots.end(); )
	{
		// Checks if inside window boundaries
		if (!(*shotIt)->checkBoundary())
		{
			Shot* remove = *shotIt;
			shotIt++;
			removeEnemyShot( remove );
			delete remove;
			continue;
		}

		shot = (*shotIt)->getCurrentCollisionOutline();

		CL_Vec2f pos = (*shotIt)->getPosition();
		shot->set_translation(pos.x, pos.y);

		if (shot->collide( *object ))
		{
			Shot* shotRemove = *shotIt;
			shotIt++;
			removeEnemyShot( shotRemove );
			delete ( shotRemove );
		}
		else
		{
			shot->set_translation(0.0f, 0.0f);
			shotIt++;
		}
	}

	// Returns player outline to 0,0
	object->set_translation(0.0f, 0.0f);
}



void TestScenePlayer::addPlayerShot( Shot* newShot )
{
	// For drawing and updating
	insertEntity( newShot );

	// For collision checking
	_playerShots.push_back( newShot );
}



void TestScenePlayer::addEnemyShot( Shot* newShot )
{
	// For drawing and updating
	insertEntity( newShot );

	// For collision checking
	_enemyShots.push_back( newShot );
}



void TestScenePlayer::removePlayerShot( Shot* shot )
{
	if (shot != NULL)
	{
		removeEntity( shot );
		_playerShots.remove( shot );
	}
}



void TestScenePlayer::removeEnemyShot( Shot* shot )
{
	if (shot != NULL)
	{
		removeEntity( shot );
		_enemyShots.remove( shot );
	}
}

/********************************************************************
	created:	2012/05/31
	created:	31:5:2012   3:26
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Player.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Player
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "Player.h"
#include "Entity.h"
#include "PlayerModelImpl.h"
#include "GameManager.h"
#include "TestScenePlayer.h"

// Logging tool
#define LOGOG_USE_PREFIX 1
#include "logog.hpp"

Player::Player(float x, float y, float speedX, float speedY, unsigned int number, std::string sprite, PlayerModel* model, 
	unsigned int lives )
	: DynamicEntity( x, y, speedX, speedY ), _playerNumber( number ), _lives( lives ), _model( model ), _spriteResourceKey( sprite )
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite(gc, sprite, manager->getResourceManager());

	// TODO: Substitute for a DynamicEntity method
	for (int i = 0; i < _currentSprite->get_frame_count(); i++)
	{
		CL_String collisionResource = cl_format( "outlines/player/rwing_00%1", i );
		_currentOutlines.push_back( new CL_CollisionOutline(collisionResource.c_str(), manager->getResourceManager()) );
	}
}



Player::~Player()
{
	delete _model;
	delete _currentSprite;
}



#ifdef _DEBUG
void Player::draw()
{
	this->DynamicEntity::draw();
	int frame = getCurrentSprite()->get_current_frame();
	_currentOutlines[frame]->draw( getPosition().x, getPosition().y, CL_Colorf::red,
		GameManager::getInstance()->getWindow()->get_gc() );
}
#endif


void Player::update()
{
	CL_InputDevice keyboard = GameManager::getInstance()->getWindow()->get_ic().get_keyboard();
	float dt = GameManager::getInstance()->getDeltaTime();

	if (keyboard.get_keycode(CL_KEY_LEFT))
	{
		setPositionX( getPosition().x - getSpeed().x * dt * 0.001f );
	}

	if (keyboard.get_keycode(CL_KEY_RIGHT))
	{
		setPositionX( getPosition().x + getSpeed().x * dt * 0.001f );
	}

	if (keyboard.get_keycode(CL_KEY_UP))
	{
		setPositionY( getPosition().y - getSpeed().y * dt * 0.001f );
	}

	if (keyboard.get_keycode(CL_KEY_DOWN))
	{
		setPositionY( getPosition().y + getSpeed().y * dt * 0.001f );
	}

	if (keyboard.get_keycode(CL_KEY_Z))
	{
		TestScenePlayer *currentScene = dynamic_cast<TestScenePlayer*>( GameManager::getInstance()->peekScene() );
		
		if (currentScene != NULL)
		{
			Shot* newShot = new Shot(getPosition().x + getCurrentSprite()->get_width()*0.5f,
				getPosition().y, 0.0f, -100.0f, "sprites/shot", 50);
			currentScene->addPlayerShot( newShot );
		}
	}

	_currentSprite->update();
}



unsigned int Player::getPlayerNumber() const 
{ 
	return _playerNumber; 
}



void Player::setPlayerNumber(unsigned int val) 
{ 
	_playerNumber = val; 
}



unsigned int Player::getLives() const 
{ 
	return _lives; 
}



void Player::setLives(unsigned int val) 
{ 
	_lives = val; 
}



void Player::addLives(unsigned int val)
{
	_lives += val;
}



void Player::subtractLives(unsigned int val)
{
	if (val <= _lives)
	{
		_lives -= val;
	}
	else
	{
		_lives = 0;
	}
}



PlayerModel* Player::getPlayerModel() const
{
	return _model;
}

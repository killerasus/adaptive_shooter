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
	: DynamicEntity( x, y, speedX, speedY ), _playerNumber( number ), _lives( lives ), _score( 0 ) ,_model( model ),
	_spriteResourceKey( sprite )
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

	_weapon = new Weapon("Standard laser", "sprites/shot", 500);
}



Player::~Player()
{
	delete _model;
	delete _currentSprite;
	delete _weapon;
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

	_weapon->update();

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
		// TODO: Adjust scene statistics
		int shots = _weapon->shoot();
	}

	_currentSprite->update();

	boundToScreen();
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



Weapon* Player::getWeapon() const
{
	return _weapon;
}



void Player::setScore( int score )
{
	_score = score;
}



int Player::getScore() const
{
	return _score;
}



void Player::addToScore( int value )
{
	_score += value;
}

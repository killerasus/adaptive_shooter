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

Player::Player( std::string sprite, PlayerModel* model, float x, float y, float speedX, float speedY, unsigned int number,
	unsigned int lives = 2 )
	: DynamicEntity( x, y, speedX, speedY ), _playerNumber( number ), _lives( lives ), _model( model )
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite(gc, sprite, manager->getResourceManager());
}



Player::~Player()
{
	delete _model;
	delete _currentSprite;
}



void Player::draw()
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite->draw(gc, getPosition().x, getPosition().y);
}



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

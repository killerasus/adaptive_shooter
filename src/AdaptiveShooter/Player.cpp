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
#include "PlayerModelImpl.h"
#include "GameManager.h"

Player::Player( std::string sprite, PlayerModel* model, float x, float y, float speedX, float speedY, unsigned int number,
	unsigned int lives = 2 )
	: _playerNumber(number), _lives(lives), _model(model), _position(x, y), _speed(speedX, speedY)
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
	_currentSprite->draw(gc, _position.x, _position.y);
}



void Player::update()
{
	CL_InputDevice keyboard = GameManager::getInstance()->getWindow()->get_ic().get_keyboard();
	float dt = GameManager::getInstance()->getDeltaTime();

	if (keyboard.get_keycode(CL_KEY_LEFT))
	{
		_position.x -= _speed.x * dt/1000.0f;
	}

	if (keyboard.get_keycode(CL_KEY_RIGHT))
	{
		_position.x += _speed.x * dt/1000.0f;
	}

	if (keyboard.get_keycode(CL_KEY_UP))
	{
		_position.y -= _speed.y * dt/1000.0f;
	}

	if (keyboard.get_keycode(CL_KEY_DOWN))
	{
		_position.y += _speed.y * dt/1000.0f;
	}

	_currentSprite->update();
}



void Player::setAlpha( float alpha )
{
	_currentSprite->set_alpha(alpha);
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



CL_Vec2f Player::getPosition() const
{
	return _position;
}



void Player::setPosition( CL_Vec2f& pos )
{
	_position.x = pos.x;
	_position.y = pos.y;
}



CL_Vec2f Player::getSpeed() const
{
	return _speed;
}



void Player::setSpeed( CL_Vec2f& speed )
{
	_speed.x = speed.x;
	_speed.y = speed.y;
}

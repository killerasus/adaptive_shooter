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
#include "KeyboardController.h"
#include "GamepadController.h"

// Logging tool
//#define LOGOG_USE_PREFIX 1
//#include "logog.hpp"

Player::Player(float x, float y, float speedX, float speedY, unsigned int number, std::string sprite, PlayerModel* model, 
	unsigned int lives )
	: DynamicEntity( x, y, speedX, speedY ), _playerNumber( number ), _lives( lives ), _score( 0 ) ,_model( model ),
	_spriteResourceKey( sprite ), _weapon( new Weapon("Standard laser", "sprites/shot", 500) ),
	_controller( GamepadController::getNewGamepad( 0 ) ), _invincible( false ), _invincibilityTimerBase(1500.0f),
	_invincibilityTimer( 0.f ), _alphaFlash( 0.5f )
{
	setCurrentWeapon( _weapon );

	if (_controller == NULL)
	{
		_controller = new KeyboardController();
	}

	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite( gc, sprite, manager->getResourceManager() );

	CL_String descriptor = sprite.substr( sprite.find_last_of( "/" ) + 1 );

	for (int i = 0; i < _currentSprite->get_frame_count(); i++)
	{
		CL_String collisionResource = cl_format( "outlines/player/%1_00%2", descriptor, i );
		_currentOutlines.push_back( new CL_CollisionOutline( collisionResource.c_str(), manager->getResourceManager() ) );
	}

}



Player::~Player()
{
	delete _model;
	delete _currentSprite;
	delete _weapon;
	delete _controller;
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
	float dt = GameManager::getInstance()->getDeltaTime();

	Shooter::update();

	updateInvincibility(dt);

	if (_controller)
	{
		if (_controller->isControllerLeft())
		{
			setPositionX( getPosition().x - getSpeed().x * dt * 0.001f );
		}

		if (_controller->isControllerRight())
		{
			setPositionX( getPosition().x + getSpeed().x * dt * 0.001f );
		}

		if (_controller->isControllerUp())
		{
			setPositionY( getPosition().y - getSpeed().y * dt * 0.001f );
		}

		if (_controller->isControllerDown())
		{
			setPositionY( getPosition().y + getSpeed().y * dt * 0.001f );
		}

		if (_controller->isControllerFire())
		{
			addShots( getCurrentWeapon()->shoot( this ) );
		}
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

	if (_lives == 1)
	{
		GameManager::getInstance()->playSoundEffect( GameManager::SFX_WARNING );
	}
}



PlayerModel* Player::getPlayerModel() const
{
	return _model;
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



void Player::addShots( std::vector<Shot*> shots )
{
	TestScenePlayer *currentScene = dynamic_cast<TestScenePlayer*>( GameManager::getInstance()->peekScene() );

	for (std::vector<Shot*>::iterator it = shots.begin(); it != shots.end(); it++)
	{
		currentScene->addPlayerShot( (*it) );
	}

	if (shots.size() > 0)
	{
		GameManager::getInstance()->playSoundEffect(GameManager::SFX_BLASTER);
	}
}



bool Player::getInvincible()
{
	return _invincible;
}



void Player::setInvincible( bool status )
{
	_invincible = status;

	if (_invincible)
	{
		_invincibilityTimer = 0.0f;
		_alphaFlash = 0.5f;
		_currentSprite->set_alpha( _alphaFlash );
	}
	else
	{
		_alphaFlash = 1.0f;
		_currentSprite->set_alpha( 1.0f );
	}
}



void Player::updateInvincibility( float dt )
{
	static int direction = 1;

	if (_invincible)
	{
		if (_invincibilityTimer >= _invincibilityTimerBase)
		{
			setInvincible( false );
		}
		else
		{
			_invincibilityTimer += dt;

			_alphaFlash = _alphaFlash + direction*dt*0.01f;

			if (_alphaFlash <= 0.0f)
			{
				direction = -direction;
				_alphaFlash = 0.0f;
			}
			else
			{
				if (_alphaFlash >= 1.0f)
				{
					direction = -direction;
					_alphaFlash = 1.0f;
				}
			}

			_currentSprite->set_alpha( _alphaFlash );
		}
	}
}

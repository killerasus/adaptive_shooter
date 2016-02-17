/********************************************************************
	created:	2012/05/24
	created:	24:5:2012   14:24
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Enemy.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Enemy
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "Enemy.h"
#include "Entity.h"
#include "GameManager.h"
#include <ClanLib/core.h>


Enemy::Enemy() : DynamicEntity(), AIAgent(), _health( 50 ), _points( 100 ), _multiplier( 1.0f ), _amplitudeLimit( 0.0f ),
	_currentAmplitude( 0.0f ), _behavior( DONTSHOOT )
{

}



Enemy::Enemy( float x, float y, float speedX, float speedY, int health, int points ) : DynamicEntity( x, y, speedX, speedY ),
	AIAgent(), _health ( health ), _points( points ), _multiplier( 1.0f ), _amplitudeLimit( 0.0f ), _currentAmplitude( 0.0f ),
	_behavior( DONTSHOOT )
{

}



Enemy::Enemy( clan::Vec2f& position, clan::Vec2f& speed, int health, int points ) : DynamicEntity ( position, speed ),
	AIAgent(), _health( health ), _points( points ), _multiplier( 1.0f ), _amplitudeLimit( 0.0f ), _currentAmplitude( 0.0f ),
	_behavior( DONTSHOOT )
{

}



Enemy::~Enemy()
{

}



void Enemy::setPoints( int points )
{
	_points = points;
}



int Enemy::getPoints()
{
	return _points;
}



void Enemy::setHealth( int health )
{
	_health = health;
}



int Enemy::getHealth()
{
	return _health;
}



float Enemy::getMultiplier()
{
	return _multiplier;
}



unsigned int Enemy::getBehavior()
{
	return _behavior;
}



void Enemy::setBehavior( unsigned int behavior )
{
	_behavior = behavior;
}



void Enemy::setAmplitudeLimit( float limit )
{
	_amplitudeLimit = limit;
}



float Enemy::getAmplitudeLimit()
{
	return _amplitudeLimit;
}

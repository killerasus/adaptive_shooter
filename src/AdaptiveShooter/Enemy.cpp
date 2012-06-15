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

void Enemy::draw()
{
	throw std::exception("The method or operation is not implemented.");
}



void Enemy::update()
{
	throw std::exception("The method or operation is not implemented.");
}



void Enemy::setAlpha( float alpha )
{
	throw std::exception("The method or operation is not implemented.");
}



void Enemy::updateStats()
{
	throw std::exception("The method or operation is not implemented.");
}



CL_Vec2f Enemy::getPosition() const
{
	return _position;
}



void Enemy::setPosition( float x, float y )
{
	_position.x = x;
	_position.y = y;
}



void Enemy::setPosition( CL_Vec2f& position )
{
	_position = position;
}



CL_Vec2f Enemy::getSpeed() const
{
	return _speed;
}



void Enemy::setSpeed( float x, float y )
{
	_speed.x = x;
	_speed.y = y;
}



void Enemy::setSpeed( CL_Vec2f& speed )
{
	_speed = speed;
}

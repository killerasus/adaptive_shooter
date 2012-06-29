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


Enemy::Enemy() : DynamicEntity(), AIAgent(), _points( 0 )
{

}



Enemy::Enemy( float x, float y, float speedX, float speedY, int points ) : DynamicEntity( x, y, speedX, speedY ), AIAgent(), _points( points )
{

}



Enemy::Enemy( CL_Vec2f& position, CL_Vec2f& speed, int points ) : DynamicEntity ( position, speed ), AIAgent(), _points( points )
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

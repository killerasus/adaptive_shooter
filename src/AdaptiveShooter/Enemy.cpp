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


Enemy::Enemy() : DynamicEntity(), AIAgent()
{

}



Enemy::Enemy( float x, float y, float speedX, float speedY ) : DynamicEntity( x, y, speedX, speedY ), AIAgent()
{

}



Enemy::Enemy( CL_Vec2f& position, CL_Vec2f& speed ) : DynamicEntity ( position, speed ), AIAgent()
{

}



Enemy::~Enemy()
{

}

/********************************************************************
	created:	2012/06/18
	created:	18:6:2012   17:42
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\DynamicEntity.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	DynamicEntity
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "DynamicEntity.h"

DynamicEntity::DynamicEntity()
{
}



DynamicEntity::DynamicEntity( float x, float y, float speedX, float speedY ) : Entity( x, y ), _speed( speedX, speedY )
{
}



DynamicEntity::DynamicEntity( CL_Vec2f& position, CL_Vec2f& speed ) : Entity( position ), _speed( speed )
{
}



DynamicEntity::~DynamicEntity()
{
}



CL_Vec2f DynamicEntity::getSpeed() const
{
	return _speed;
}



void DynamicEntity::setSpeed( float x, float y )
{
	_speed.x = x;
	_speed.y = y;
}



void DynamicEntity::setSpeed( CL_Vec2f& speed )
{
	_speed = speed;
}

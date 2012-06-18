/********************************************************************
	created:	2012/06/18
	created:	18:6:2012   17:09
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Entity.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Entity
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "Entity.h"

Entity::Entity()
{
}



Entity::Entity( CL_Vec2f& position ):_currentSprite(0), _position(position)
{
}



Entity::Entity( float x, float y ):_currentSprite(0), _position(x, y)
{
}



Entity::~Entity()
{
}



CL_Vec2f Entity::getPosition() const
{
	return _position;
}



void Entity::setPosition( CL_Vec2f& position )
{
	_position = position;
}



void Entity::setPosition( float x, float y )
{
	_position.x = x;
	_position.y = y;
}




void Entity::setPositionX( float x )
{
	_position.x = x;
}



void Entity::setPositionY( float y )
{
	_position.y = y;
}



CL_Sprite* Entity::getCurrentSprite() const
{
	return _currentSprite;
}



float Entity::getAlpha() const
{
	if (_currentSprite)
		return _currentSprite->get_alpha();
	else
		return -1;
}



void Entity::setAlpha(float alpha)
{
	if (_currentSprite)
		_currentSprite->set_alpha( alpha );
}

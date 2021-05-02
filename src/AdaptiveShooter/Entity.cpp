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
#include "GameManager.h"

Entity::Entity() : _position(0.0f, 0.0f)
{}

Entity::Entity( clan::Vec2f& position ): _position(position)
{}

Entity::Entity( float x, float y ): _position(x, y)
{}

Entity::~Entity()
{}

clan::Vec2f Entity::getPosition() const
{ return _position; }

void Entity::setPosition( clan::Vec2f& position )
{ _position = position; }

void Entity::setPosition( float x, float y )
{
	_position.x = x;
	_position.y = y;
}

void Entity::setPositionX( float x )
{ _position.x = x; }

void Entity::setPositionY( float y )
{ _position.y = y; }

clan::Sprite& Entity::getCurrentSprite() const
{ return const_cast<clan::Sprite&>(_currentSprite); }

float Entity::getAlpha() const
{ return _currentSprite.get_alpha(); }

void Entity::setAlpha(float alpha)
{
	_currentSprite.set_alpha( alpha );
}



bool Entity::checkWindowBoundary()
{
	clan::GraphicContext& gc = GameManager::getInstance()->getWindow()->get_gc();
	float top, bottom, left, right;

	top = _position.y;
	left = _position.x;
	right = left + _currentSprite.get_width();
	bottom = top + _currentSprite.get_height();

	if (bottom < 0.0f || right < 0.0f || top > gc.get_height() || left > gc.get_width())
		return false;
	else
		return true;
}

unsigned int Entity::boundToScreen()
{
	unsigned int collision = CD_NOCOLLISION;
	clan::GraphicContext& gc = GameManager::getInstance()->getWindow()->get_gc();
	float top, bottom, left, right;

	top = _position.y;
	left = _position.x;
	right = left + _currentSprite.get_width();
	bottom = top + _currentSprite.get_height();

	if (bottom > gc.get_height())
	{
		_position.y = (float)(gc.get_height() - _currentSprite.get_height());
		collision |= CD_BOTTOM;
	} 
	
	if (right > gc.get_width())
	{
		_position.x = (float)(gc.get_width() - _currentSprite.get_width());
		collision |= CD_RIGHT;
	}
	
	if (top < 0.0f)
	{
		_position.y = 0.0f;
		collision |= CD_TOP;
	}
	
	if (left < 0.0f)
	{
		_position.x = 0.0f;
		collision |= CD_LEFT;
	}

	return collision;
}

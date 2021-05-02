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
#include "GameManager.h"

DynamicEntity::DynamicEntity()
{}

DynamicEntity::DynamicEntity( float x, float y, float speedX, float speedY ) : Entity( x, y ), _speed( speedX, speedY )
{}

DynamicEntity::DynamicEntity( clan::Vec2f& position, clan::Vec2f& speed ) : Entity( position ), _speed( speed )
{}

DynamicEntity::~DynamicEntity()
{}

void DynamicEntity::draw()
{
	GameManager* manager = GameManager::getInstance();
	clan::Canvas& canvas = manager->getCanvas();
	_currentSprite.draw( canvas, getPosition().x, getPosition().y );
}

clan::Vec2f DynamicEntity::getSpeed() const
{ return _speed; }

void DynamicEntity::setSpeed( float x, float y )
{
	_speed.x = x;
	_speed.y = y;
}

void DynamicEntity::setSpeed( clan::Vec2f& speed )
{ _speed = speed; }

void DynamicEntity::setSpeedX( float x )
{ _speed.x = x; }

void DynamicEntity::setSpeedY( float y )
{ _speed.y = y; }

const clan::CollisionOutline& DynamicEntity::getCurrentCollisionOutline() const
{
	int i = getCurrentSprite().get_current_frame();
	return _currentOutlines[i];
}

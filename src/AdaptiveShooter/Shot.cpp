/********************************************************************
	created:	2012/06/19
	created:	19:6:2012   17:06
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Shot.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Shot
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "Shot.h"
#include "GameManager.h"
#include <ClanLib/core.h>

Shot::Shot( std::string resource ) : DynamicEntity(), _damage( 0 )
{
	GameManager* manager = GameManager::getInstance();
	clan::Canvas& gc = manager->getCanvas();
	_currentSprite = clan::Sprite::resource( gc, resource, manager->getResourceManager() );

	std::string descriptor = resource.substr(resource.find_last_of("/") + 1);

	for (int i = 0; i < _currentSprite.get_frame_count(); i++)
	{
		std::string collisionResource = clan::string_format( "outlines/%1/%2_00%3", descriptor, descriptor, i );
		_currentOutlines.push_back( clan::CollisionOutline::load(collisionResource.c_str(), manager->getResourceDocument()) );
	}
}



Shot::Shot( float x, float y, float speedX, float speedY, std::string resource, int damage ) : DynamicEntity( x, y, speedX, speedY ), _damage( damage )
{
	GameManager* manager = GameManager::getInstance();
	clan::Canvas& gc = manager->getCanvas();
	_currentSprite = clan::Sprite::resource( gc, resource, manager->getResourceManager() );

	std::string descriptor = resource.substr(resource.find_last_of("/") + 1);

	for (int i = 0; i < _currentSprite.get_frame_count(); i++)
	{
		std::string collisionResource = clan::string_format( "outlines/%1/%2_00%3", descriptor, descriptor, i );
		_currentOutlines.push_back( clan::CollisionOutline::load(collisionResource.c_str(), manager->getResourceDocument()) );
	}
}



Shot::Shot( clan::Vec2f& position, clan::Vec2f& speed, std::string resource, int damage ) : DynamicEntity( position, speed ), _damage( damage )
{
	GameManager* manager = GameManager::getInstance();
	clan::Canvas& gc = manager->getCanvas();
	_currentSprite = clan::Sprite::resource( gc, resource, manager->getResourceManager() );

	std::string descriptor = resource.substr(resource.find_last_of("/") + 1);

	for (int i = 0; i < _currentSprite.get_frame_count(); i++)
	{
		std::string collisionResource = clan::string_format( "outlines/%1/%2_00%3", descriptor, descriptor, i );
		_currentOutlines.push_back( clan::CollisionOutline::load(collisionResource.c_str(), manager->getResourceDocument()) );
	}
}



Shot::~Shot()
{
}



#ifdef _DEBUG
void Shot::draw()
{
	this->DynamicEntity::draw();
	int frame = getCurrentSprite().get_current_frame();
	_currentOutlines[frame].draw( getPosition().x, getPosition().y, clan::Colorf::red,
		GameManager::getInstance()->getCanvas() );
}
#endif


void Shot::update()
{
	int dt = GameManager::getInstance()->getDeltaTime();
	setPosition( getPosition().x + getSpeed().x * dt * 0.001f, getPosition().y + getSpeed().y * dt * 0.001f );
	_currentSprite.update( dt );
}



void Shot::setDamage( int damage )
{
	_damage = damage;
}



int Shot::getDamage() const
{
	return _damage;
}

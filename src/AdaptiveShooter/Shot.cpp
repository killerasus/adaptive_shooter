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
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite( gc, resource, manager->getResourceManager() );

	CL_String descriptor = resource.substr(resource.find_last_of("/") + 1);

	for (int i = 0; i < _currentSprite->get_frame_count(); i++)
	{
		CL_String collisionResource = cl_format( "outlines/%1/%2_00%3", descriptor, descriptor, i );
		_currentOutlines.push_back( new CL_CollisionOutline(collisionResource.c_str(), manager->getResourceManager()) );
	}
}



Shot::Shot( float x, float y, float speedX, float speedY, std::string resource, int damage ) : DynamicEntity( x, y, speedX, speedY ), _damage( damage )
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite( gc, resource, manager->getResourceManager() );

	CL_String descriptor = resource.substr(resource.find_last_of("/") + 1);

	for (int i = 0; i < _currentSprite->get_frame_count(); i++)
	{
		CL_String collisionResource = cl_format( "outlines/%1/%2_00%3", descriptor, descriptor, i );
		_currentOutlines.push_back( new CL_CollisionOutline(collisionResource.c_str(), manager->getResourceManager()) );
	}
}



Shot::Shot( CL_Vec2f& position, CL_Vec2f& speed, std::string resource, int damage ) : DynamicEntity( position, speed ), _damage( damage )
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite( gc, resource, manager->getResourceManager() );

	CL_String descriptor = resource.substr(resource.find_last_of("/") + 1);

	for (int i = 0; i < _currentSprite->get_frame_count(); i++)
	{
		CL_String collisionResource = cl_format( "outlines/%1/%2_00%3", descriptor, descriptor, i );
		_currentOutlines.push_back( new CL_CollisionOutline(collisionResource.c_str(), manager->getResourceManager()) );
	}
}



Shot::~Shot()
{
	delete _currentSprite;

#ifdef _DEBUG
	CL_Console::write_line("Deleted a shot");
#endif
}



#ifdef _DEBUG
void Shot::draw()
{
	this->DynamicEntity::draw();
	int frame = getCurrentSprite()->get_current_frame();
	_currentOutlines[frame]->draw( getPosition().x, getPosition().y, CL_Colorf::red,
		GameManager::getInstance()->getWindow()->get_gc() );
}
#endif


void Shot::update()
{
	float dt = GameManager::getInstance()->getDeltaTime();
	setPosition( getPosition().x + getSpeed().x * dt * 0.001f, getPosition().y + getSpeed().y * dt * 0.001f );
	_currentSprite->update();
}



void Shot::setDamage( int damage )
{
	_damage = damage;
}



int Shot::getDamage() const
{
	return _damage;
}

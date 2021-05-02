/********************************************************************
	created:	2011/12/06
	created:	6:12:2011   19:51
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\TestEntity.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	StaticEntity
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "StaticEntity.h"
#include "GameManager.h"

StaticEntity::StaticEntity(float x, float y, std::string resource_id):Entity( x, y )
{
	GameManager* manager = GameManager::getInstance();
	clan::Canvas& gc = manager->getCanvas();

	_currentSprite = clan::Sprite::resource(gc, resource_id, manager->getResourceManager());
}

StaticEntity::~StaticEntity()
{}

void StaticEntity::draw()
{ _currentSprite.draw( GameManager::getInstance()->getCanvas(), getPosition().x, getPosition().y ); }

void StaticEntity::update()
{ _currentSprite.update( GameManager::getInstance()->getDeltaTime() ); }

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
	CL_GraphicContext gc = manager->getWindow()->get_gc();

	_currentSprite = new CL_Sprite(gc, resource_id, manager->getResourceManager());
}



StaticEntity::~StaticEntity()
{
	delete _currentSprite;
}



void StaticEntity::draw()
{
	_currentSprite->draw( GameManager::getInstance()->getWindow()->get_gc(), getPosition().x, getPosition().y );
}



void StaticEntity::update()
{
	_currentSprite->update();
}

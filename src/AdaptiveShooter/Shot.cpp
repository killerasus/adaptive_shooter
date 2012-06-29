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

Shot::Shot( std::string resource ) : DynamicEntity()
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite( gc, resource, manager->getResourceManager() );
}



Shot::Shot( float x, float y, float speedX, float speedY, std::string resource ) : DynamicEntity( x, y, speedX, speedY )
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite( gc, resource, manager->getResourceManager() );
}



Shot::Shot( CL_Vec2f& position, CL_Vec2f& speed, std::string resource ) : DynamicEntity( position, speed )
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite( gc, resource, manager->getResourceManager() );
}



Shot::~Shot()
{
	delete _currentSprite;
}



void Shot::update()
{
	float dt = GameManager::getInstance()->getDeltaTime();
	setPosition( getPosition().x + getSpeed().x * dt * 0.001f, getPosition().y + getSpeed().y * dt * 0.001f );
	CL_Vec2f position = getPosition();

	CL_Size windowSize = GameManager::getInstance()->getWindow()->get_gc().get_size();
	CL_Size spriteSize = getCurrentSprite()->get_size();

	//Checks if sprite is trying to get outside window horizontally
	if (position.x + spriteSize.width > windowSize.width)
	{
		//TODO: 
	}
	else
	{
		if (position.x < 0.0f)
		{
			//TODO:
		}
	}

	//Checks if sprite is trying to get outside window view vertically
	if (position.y + spriteSize.height < 0.0f)
	{
		//TODO:
	} 
	else
	{
		if (position.y > windowSize.height)
		{
			//TODO:
		}
	}
}

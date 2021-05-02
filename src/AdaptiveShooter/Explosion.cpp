/********************************************************************
	created:	2012/07/28
	created:	28:7:2012   18:29
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Explosion.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Explosion
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "Explosion.h"
#include "Scene.h"
#include "GameManager.h"

Explosion::Explosion( float x, float y, float speedX, float speedY, std::string resource ) : DynamicEntity( 0.0f, 0.0f, speedX, speedY )
{
	GameManager* manager = GameManager::getInstance();
	clan::Canvas& canvas = manager->getCanvas();
	_currentSprite = clan::Sprite::resource( canvas, resource, manager->getResourceManager() );

	// Adjusts the x, y that represent the center to the top left of the sprite
	setPosition( x - _currentSprite.get_width()*0.5f, y - _currentSprite.get_height()*0.5f );
}

Explosion::~Explosion()
{}

void Explosion::update()
{
	int dt = GameManager::getInstance()->getDeltaTime();
	setPosition( getPosition().x + getSpeed().x * dt * 0.001f, getPosition().y + getSpeed().y * dt * 0.001f );
	_currentSprite.update( static_cast<int>(dt) );

	if (getCurrentSprite().is_finished())
		GameManager::getInstance()->peekScene()->pushEntityToDelete( this );
}

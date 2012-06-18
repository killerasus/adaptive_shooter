/********************************************************************
	created:	2012/05/24
	created:	24:5:2012   14:24
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Enemy.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Enemy
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "Enemy.h"
#include "Entity.h"
#include "GameManager.h"

void Enemy::draw()
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	getCurrentSprite()->draw(gc, getPosition().x, getPosition().y);
}



void Enemy::update()
{
	throw std::exception("The method or operation is not implemented.");
}



void Enemy::updateStats()
{
	throw std::exception("The method or operation is not implemented.");
}

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

Shot::Shot( std::string resource ) : DynamicEntity()
{
	//GameManager::getInstance()->getResourceManager()->
}



Shot::Shot( float x, float y, float speedX, float speedY, std::string resource ) : DynamicEntity( x, y, speedX, speedY )
{

}



Shot::Shot( CL_Vec2f& position, CL_Vec2f& speed, std::string resource ) : DynamicEntity( position, speed )
{

}



Shot::~Shot()
{

}



void Shot::draw()
{

}



void Shot::update()
{

}

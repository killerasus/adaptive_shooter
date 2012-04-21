/********************************************************************
	created:	2012/01/04
	created:	4:1:2012   4:28
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\MenuItem.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	MenuItem
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Implementation of MenuItem
*********************************************************************/
#include "MenuItem.h"
#include "GameManager.h"
#include <string>

MenuItem::MenuItem(float x, float y, std::string notSelectedResource_id, std::string SelectedResource_id):
_pos(x,y)
{
	CL_ResourceManager *manager = GameManager::GetInstance()->GetResourceManager();
}

MenuItem::~MenuItem()
{

}

void MenuItem::draw()
{
	_sprite->draw( GameManager::GetInstance()->GetWindow()->get_gc(), _pos.x, _pos.y );
}

void MenuItem::update()
{
	_sprite->update();
}

void MenuItem::setAlpha( float alpha )
{
	_sprite->set_alpha(alpha);
}

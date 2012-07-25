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

MenuItem::MenuItem( float x, float y, std::string selectedResource_id, std::string notSelectedResource_id ):
Entity( x, y ), _isSelected( false )
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_notSelected = new CL_Sprite( gc, notSelectedResource_id, manager->getResourceManager() );
	_selected = new CL_Sprite( gc, selectedResource_id, manager->getResourceManager() );
	_currentSprite = _notSelected;
}



MenuItem::~MenuItem()
{
	delete _notSelected;
	delete _selected;
}



void MenuItem::draw()
{
	getCurrentSprite()->draw( GameManager::getInstance()->getWindow()->get_gc(), getPosition().x, getPosition().y );
}



void MenuItem::update()
{
	getCurrentSprite()->update();
}



void MenuItem::setSelected( bool selected )
{
	_isSelected = selected;

	_currentSprite = _isSelected ? _selected : _notSelected;
}



bool MenuItem::getSelected()
{
	return _isSelected;
}

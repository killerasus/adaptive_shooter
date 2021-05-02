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
	clan::Canvas& gc = manager->getCanvas();
	_notSelected = clan::Sprite::resource( gc, notSelectedResource_id, manager->getResourceManager() );
	_selected = clan::Sprite::resource( gc, selectedResource_id, manager->getResourceManager() );
	_currentSprite = _notSelected;
}

MenuItem::~MenuItem()
{}

void MenuItem::draw()
{ getCurrentSprite().draw( GameManager::getInstance()->getCanvas(), getPosition().x, getPosition().y ); }

void MenuItem::update()
{ getCurrentSprite().update( GameManager::getInstance()->getDeltaTime() ); }

void MenuItem::setSelected( bool selected )
{
	_isSelected = selected;
	_currentSprite = _isSelected ? _selected : _notSelected;
}

bool MenuItem::getSelected()
{ return _isSelected; }

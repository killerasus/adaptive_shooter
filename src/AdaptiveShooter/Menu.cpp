/********************************************************************
	created:	2012/01/04
	created:	4:1:2012   4:20
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Menu.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Menu
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Implementation of Menu class
*********************************************************************/

#include "Menu.h"
#include "GameManager.h"
#include "StaticEntity.h"

Menu::Menu()
{
	_sceneState = SS_RUNNING;
	_entities.push_back(new StaticEntity(0,0,"background_menu"));
}

Menu::~Menu()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		delete _entities[i];
	}
}

void Menu::update()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		_entities[i]->update();
	}

	//Insert code for menu state transition
}
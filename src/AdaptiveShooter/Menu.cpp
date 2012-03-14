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
	_menuState = 0;
}

Menu::~Menu()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		delete _entities[i];
	}
}

/* Override */
void Menu::update()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		_entities[i]->update();
	}

	//Insert code for menu state transition
	CL_InputContext ic = GameManager::GetInstance()->GetWindow()->get_ic();
	CL_InputDevice keyboard = ic.get_keyboard();
	CL_InputDevice joystick = ic.get_joystick();

	if (keyboard.get_keycode(CL_KEY_DOWN))
	{
		StateDown();
	}

	if (keyboard.get_keycode(CL_KEY_UP))
	{
		StateUp();
	}

	if (keyboard.get_keycode(CL_KEY_ENTER))
	{
		ExecuteState();
	}
}

/* Override */
void Menu::draw()
{
	Scene::draw();

	//Specific drawing code for _menuOptions and _menuPointer

}

void Menu::StateDown()
{
	if ( _menuState < _menuItems.size() - 1 )
	{
		_menuState++;
	}
}

void Menu::StateUp()
{
	if ( _menuState > 0 )
	{
		_menuState--;
	}
}

void Menu::ExecuteState()
{

}

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
#include "GamepadController.h"
#include "KeyboardController.h"

Menu::Menu() : Scene(), _menuState( 0 ), _controller( GamepadController::getNewGamepad( 0 ) ), _inputDelay( 250.f ),
	_inputeTimer( 0.0f ), _canExecute( true )
{
	_sceneState = SS_RUNNING;
	
	if (_controller == NULL)
		_controller = new KeyboardController();
}

Menu::~Menu()
{ delete _controller; }

/* Override */
void Menu::update()
{
	for (std::list<Entity*>::iterator it = _entities.begin(); it != _entities.end(); it++)
		(*it)->update();

	if (!_canExecute)
	{
		int dt = GameManager::getInstance()->getDeltaTime();
		_inputeTimer += dt;

		if (_inputeTimer >= _inputDelay)
		{
			_canExecute = true;
			_inputeTimer = 0.0f;
		}
		else
			return;
	}

	if (_controller->isControllerDown())
	{
		_canExecute = false;
		StateDown();
	}

	if (_controller->isControllerUp())
	{
		_canExecute = false;
		StateUp();
	}

	if (_controller->isControllerFire())
	{
		_canExecute = false;
		GameManager::getInstance()->playSoundEffect( GameManager::SFX_MENU_SELECT );
		ExecuteState();
	}
}

/* Override */
void Menu::draw()
{ Scene::draw(); }

unsigned int Menu::getMenuState() const
{ return _menuState; }

void Menu::StateDown()
{
	if ( _menuState < _menuItems.size() - 1 )
	{
		GameManager::getInstance()->playSoundEffect( GameManager::SFX_MENU_PICK );
		_menuItems[_menuState]->setSelected( false );
		++_menuState;
		_menuItems[_menuState]->setSelected( true );
	}
}

void Menu::StateUp()
{
	if ( _menuState > 0 )
	{
		GameManager::getInstance()->playSoundEffect( GameManager::SFX_MENU_PICK );
		_menuItems[_menuState]->setSelected( false );
		--_menuState;
		_menuItems[_menuState]->setSelected( true );
	}
}

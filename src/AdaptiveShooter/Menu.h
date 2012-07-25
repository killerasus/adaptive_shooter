/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   8:25
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\Menu.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	Menu
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Menu and MenuState class definitions
*********************************************************************/

#ifndef Menu_h__
#define Menu_h__

#include "Scene.h"
#include "MenuItem.h"
#include "ControllerInterface.h"

/**
 * Menu is a class for handling menu-like interfaces for changing game options
 */
class Menu : virtual public Scene
{
public:
	Menu();
	virtual ~Menu();

	virtual void update();
	virtual void draw();

	/**
	 * Gets the current menu state
	 * 
	 * @return	unsigned int	Menu state
	 */
	unsigned int getMenuState() const;

protected:
	void StateDown();
	void StateUp();
	virtual void ExecuteState() = 0;

	std::vector<MenuItem*> _menuItems;

private:
	unsigned int _menuState;
	Entity* _menuPointer;
	ControllerInterface* _controller;
	float _inputDelay;	// Delay in milisseconds for input check in menu
	float _inputeTimer;
	bool _canExecute;
};

#endif // Menu_h__
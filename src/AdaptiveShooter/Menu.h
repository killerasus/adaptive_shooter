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

/**
 * Menu is a class for handling menu-like interfaces for changing game options
 */
class Menu : public Scene
{
public:
	Menu();
	~Menu();

	virtual void update();
protected:
private:
};

#endif // Menu_h__
/********************************************************************
	created:	2012/07/19
	created:	19:7:2012   13:09
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\Jogo\src\AdaptiveShooter\KeyboardController.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\Jogo\src\AdaptiveShooter
	file base:	KeyboardController
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Implementation of keyboard based controller
*********************************************************************/

#ifndef KeyboardController_h__
#define KeyboardController_h__

#include "ControllerInterface.h"
#include "ClanLib/core.h"
#include "ClanLib/display.h"

class KeyboardController : public ControllerInterface
{
public:
	KeyboardController();

	~KeyboardController();

	virtual bool isControllerUp();

	virtual bool isControllerDown();

	virtual bool isControllerLeft();

	virtual bool isControllerRight();

	virtual bool isControllerFire();

	virtual bool isControllerBomb();

	virtual bool isControllerBack();

	virtual bool isControllerStart();

protected:
	
private:
	CL_InputDevice _keyboard;
};

#endif // KeyboardController_h__
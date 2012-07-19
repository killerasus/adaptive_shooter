/********************************************************************
	created:	2012/07/19
	created:	19:7:2012   13:14
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\Jogo\src\AdaptiveShooter\KeyboardController.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\Jogo\src\AdaptiveShooter
	file base:	KeyboardController
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Implementation of keyboard based controller interface
*********************************************************************/

#include "KeyboardController.h"
#include "GameManager.h"

KeyboardController::KeyboardController() : 
	_keyboard(GameManager::getInstance()->getWindow()->get_ic().get_keyboard())
{

}



KeyboardController::~KeyboardController()
{

}



bool KeyboardController::isControllerUp()
{
	return _keyboard.get_keycode( CL_KEY_UP );
}



bool KeyboardController::isControllerDown()
{
	return _keyboard.get_keycode( CL_KEY_DOWN );
}



bool KeyboardController::isControllerLeft()
{
	return _keyboard.get_keycode( CL_KEY_LEFT );
}



bool KeyboardController::isControllerRight()
{
	return _keyboard.get_keycode( CL_KEY_RIGHT );
}



bool KeyboardController::isControllerFire()
{
	return _keyboard.get_keycode( CL_KEY_Z );
}



bool KeyboardController::isControllerBomb()
{
	return _keyboard.get_keycode( CL_KEY_X );
}



bool KeyboardController::isControllerBack()
{
	return _keyboard.get_keycode( CL_KEY_ESCAPE );
}



bool KeyboardController::isControllerStart()
{
	return _keyboard.get_keycode( CL_KEY_ENTER );
}



/********************************************************************
	created:	2012/07/19
	created:	19:7:2012   14:17
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\Jogo\src\AdaptiveShooter\GamepadController.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\Jogo\src\AdaptiveShooter
	file base:	GamepadController
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "GamepadController.h"
#include "GameManager.h"


GamepadController* GamepadController::getNewGamepad( int number )
{
	int numJoysticks = GameManager::getInstance()->getWindow()->get_ic().get_joystick_count();

	if ( numJoysticks > 0 && number < numJoysticks )
	{
		return new GamepadController( number );
	} 
	else
	{
		return NULL;
	}
}



GamepadController::~GamepadController()
{

}



GamepadController::GamepadController( int number ) :
	_gamepad( GameManager::getInstance()->getWindow()->get_ic().get_joystick( number ) ),
	_deadzone( 0.2f )
{

}



bool GamepadController::isControllerUp()
{
	if ( _gamepad.get_axis( GP_Y_AXIS ) < -_deadzone )
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool GamepadController::isControllerDown()
{
	if ( _gamepad.get_axis( GP_Y_AXIS ) > _deadzone )
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool GamepadController::isControllerLeft()
{
	if ( _gamepad.get_axis( GP_X_AXIS ) < -_deadzone )
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool GamepadController::isControllerRight()
{
	if ( _gamepad.get_axis( GP_X_AXIS ) > _deadzone )
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool GamepadController::isControllerFire()
{
	return _gamepad.get_keycode( GP_BUTTON_X );
}



bool GamepadController::isControllerBomb()
{
	return _gamepad.get_keycode( GP_BUTTON_A );
}



bool GamepadController::isControllerBack()
{
	return _gamepad.get_keycode( GP_BUTTON_B );
}



bool GamepadController::isControllerStart()
{
	return _gamepad.get_keycode( GP_BUTTON_START );
}

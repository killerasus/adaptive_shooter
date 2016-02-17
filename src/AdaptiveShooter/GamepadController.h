/********************************************************************
	created:	2012/07/19
	created:	19:7:2012   14:03
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\Jogo\src\AdaptiveShooter\GamepadController.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\Jogo\src\AdaptiveShooter
	file base:	GamepadController
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Implementation of gamepad based controller
*********************************************************************/

#ifndef GamepadController_h__
#define GamepadController_h__

#include "ControllerInterface.h"
#include "ClanLib/core.h"
#include "ClanLib/display.h"

class GamepadController : public ControllerInterface
{
public:
	
	/**
	 *	Creates a new controller for the controller number passed.
	 *
	 * @param[in]	number				Number of the controller to get. Range: [0..3]
	 * @return		GamepadController*	Pointer to controller. NULL if no controller with the number passed.
	 */
	static GamepadController* getNewGamepad( int number );

	~GamepadController();

	virtual bool isControllerUp();

	virtual bool isControllerDown();

	virtual bool isControllerLeft();

	virtual bool isControllerRight();

	virtual bool isControllerFire();

	virtual bool isControllerBomb();

	virtual bool isControllerBack();

	virtual bool isControllerStart();

	enum GamepadKeys
	{
		GP_X_AXIS = 0,
		GP_Y_AXIS,
		GP_Z_AXIS,
		GP_BUTTON_A = 0,
		GP_BUTTON_B,
		GP_BUTTON_X,
		GP_BUTTON_Y,
		GP_BUTTON_L,
		GP_BUTTON_R,
		GP_BUTTON_SELECT,
		GP_BUTTON_START,
		GP_BUTTON_L_HATCH,
		GP_BUTTON_R_HATCH
	};
private:

	/**
	 * Constructor
	 *
	 * @param[in]	number	Controller number
	 */
	GamepadController( int number );

	clan::InputDevice _gamepad;
	float _deadzone;
};

#endif // GamepadController_h__